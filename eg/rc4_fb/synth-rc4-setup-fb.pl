#!/usr/bin/perl

use strict;

$| = 1;

die "Usage: synth-rc4-enc-fb.pl <seed> <default adaptor(0=zero,1=identity) [<lower bound for constant> <upper bound for constant>]"
  unless @ARGV == 4;
my($rand_seed, $default_adaptor_pref, $const_lb, $const_ub) = @ARGV;

srand($rand_seed);
my $unused_1=`ulimit -s unlimited`;
die "failed to set ulimit" unless $unused_1== 0;
# Configurables
my $split_target_formulas=1;
my $path_depth_limit = 300;
my $iteration_limit = 4000;
my $mo_adapter = 1;
my $trace_verbose = 0;
# the f2 iteration limit needs to be 2 for the O <- M case because mbedtls's 
# RC4 encryption function has a loop which requires two instructions to be
# executed twice to check the loop termination condition at the end of every
# loop iteration
# the f2 iteration limit needs to be 1 for the M <- O case because OpenSSL's
# RC4 encyption function does not have such a loop but instead it has repeated
# code that checks the termination condition if the length is less than 8
my $arr_len = 4;
my $iteration_f2_limit=$arr_len+1;
#if ($mo_adapter == 0) { $iteration_f2_limit = 2; }
#elsif($mo_adapter == 1) { $iteration_f2_limit = 1; }

my $table_treatment = 1;

my $adaptor_ivc = 1;

my $n_fields = 2;
my $starting_sane_addr = 0x42420000;

my $max_steps = 1000;
#my $key_const_val = 1;
# End configurables

my $max_struct_size=2*4 + $arr_len*4;
my $sane_addr = $starting_sane_addr;
my $max_conc_region_size = $max_struct_size;
my $output_string_addr = 0x42000000;
my $input_string_length = 1;
my $input_string_addr = $output_string_addr + 2*$max_conc_region_size;
my $region_limit = $max_conc_region_size;
my @fuzzball_extra_args_arr;

my $fuzzball="./fuzzball";
my $stp="./stp";#"./stp-2.1.2"; #="./stp-wrapper";

my $f1_completed_count = 0;
my $iteration_count = 0;

my $bin = "./rc4enc";

print "compiling binary: ";
my $gcc_var;
if ($mo_adapter == 1) { $gcc_var = "MO_ADAPTER=1"; }
elsif ($mo_adapter == 0) { $gcc_var = "OM_ADAPTER=1"; }
my $unused = `gcc -DRC4SETUP=1 -D$gcc_var -DARR_LEN=$arr_len -static $bin.c -Wl,-rpath,/export/scratch/vaibhav/opt_openssl/lib -g -o $bin -lcrypto -I /export/scratch/vaibhav/mbedtls-install/include/`;
my $gcc_ec = $?;
die "failed to compile $bin" unless $gcc_ec == 0;
print "gcc_ec = $gcc_ec\n";

# Try to figure out the code and data addresses we need based on
# matching the output of "nm" and "objdump". Not the most robust
# possible approach.

my $fuzz_start_addr = "0x" . substr(`nm $bin | fgrep " T fuzz_start"`, 0, 16);

my $f1_addr = "0x" . substr(`nm $bin | fgrep " T f1"`, 0, 16);

my $f1_call_addr =
  "0x" . substr(`objdump -dr $bin | grep 'call.*<f1>'`, 2, 6);

my $f2_addr = "0x" . substr(`nm $bin | fgrep " T f2"`, 0, 16);

my $wrap_f2_addr = "0x" . substr(`nm $bin | fgrep " T wrap_f2"`, 0, 16);

my $f2_call_addr =
  "0x" . substr(`objdump -dr $bin | grep 'call.*<wrap_f2>'`, 2, 6);

my $post_f1_call = sprintf("0x%x",hex($f1_call_addr)+0x5);
my $post_f2_call = sprintf("0x%x",hex($f2_call_addr)+0x5);

my $match_jne_addr =
  "0x" . substr(`objdump -dr $bin | grep 'jne.*compare+'`, 2, 6);

print "$fuzzball\n";
print "$stp\n";
print "fuzz-start-addr : $fuzz_start_addr\n";
print "f1:   $f1_addr @ $f1_call_addr\n";
print "f2:   $f2_addr\n";
print "wrap_f2: $wrap_f2_addr @ $f2_call_addr\n";
print "branch: $match_jne_addr\n";

my($fields_addr);

# Field [0]: field name
# Field [1]: Vine type
# Field [2]: printf format for the string form

my @fields =
  (["a_is_const",  "reg1_t", "%01x"],
   ["a_val",      "reg64_t", "%016x"],
   ["b_is_const",  "reg1_t", "%01x"],
   ["b_val",      "reg64_t", "%016x"],
   ["c_is_const",  "reg1_t", "%01x"],
   ["c_val",      "reg64_t", "%016x"],
   ["d_is_const",  "reg1_t", "%01x"],
   ["d_val",      "reg64_t", "%016x"],
   ["e_is_const",  "reg1_t", "%01x"],
   ["e_val",      "reg64_t", "%016x"],
   ["f_is_const",  "reg1_t", "%01x"],
   ["f_val",      "reg64_t", "%016x"],
);

my @ret_fields = 
(
   ["ret_type",  "reg8_t", "%01x"],
   ["ret_val",   "reg64_t", "%016x"],
);

my @struct_fields = ();
for (my $i =1; $i <= $n_fields; $i++) {
    my $f_type_str = sprintf("f%d_type", $i);
    my $field_size_str = sprintf("f%d_size", $i);
    my $field_n_str = sprintf("f%d_n", $i);
    push @struct_fields, [$f_type_str, "reg64_t", "%01x"];
    push @struct_fields, [$field_size_str, "reg16_t", "%01x"];
    push @struct_fields, [$field_n_str, "reg16_t", "%01x"];
}

my($f1nargs, $f2nargs) = (3,3);
splice(@fields, 2 * $f2nargs);

my @solver_opts = ("-solver", "smtlib", "-solver-path", $stp, "-smtlib-solver-type","stp"
		    #,"-save-solver-files"
);

my @synth_opt = ("-synthesize-adaptor",
		 join(":", "simple", $f2_call_addr, $f1nargs, $f2_addr, $f2nargs));

my @synth_ret_opt = ("-synthesize-return-adaptor",
		 join(":", "return-typeconv", $f2_addr, $post_f2_call, $f2nargs));
print "synth_ret_opt = @synth_ret_opt\n";

my @synth_struct_opt;

sub reinitialize_synth_struct_opt  {
    my($is_ce) = (@_);
    my $steps = ($sane_addr - $starting_sane_addr)/$max_conc_region_size;
    @synth_struct_opt = ();
    if( $is_ce == 0) {
	for (my $s=0; $s < $steps; $s++ ) {
	    push @synth_struct_opt, "-synthesize-struct-adaptor";
	    my $tmp_str;
	    if ($s < $steps) {
		push @synth_struct_opt, sprintf("0x%x", ($starting_sane_addr + ($s * $max_conc_region_size)) );
	    }
	}
    } else {
	push @synth_struct_opt, "-synthesize-struct-adaptor";
	push @synth_struct_opt, $sane_addr;
    }
    push @synth_struct_opt, "-struct-adaptor-params";
    push @synth_struct_opt, sprintf("%d:%d:%d", $n_fields, $n_fields, $max_struct_size);
    for my $i (0 ..  $#synth_struct_opt) {
    	print "synth_struct_opt[$i] = $synth_struct_opt[$i]\n";
    }
    if($split_target_formulas==1) {
	push @synth_struct_opt, "-split-target-formulas";
    }
    if($adaptor_ivc==1) {
	push @synth_struct_opt, "-adaptor-ivc";
    }
}

reinitialize_synth_struct_opt(1); 

my @const_bounds_ec = ();
if($const_lb != $const_ub) {
    for (my $i=0; $i<$f2nargs; $i++) {
	my $n = chr(97 + $i);
	my $s1='';
	my $s2='';
	if($f1nargs != 0) {
	    $s1 = sprintf("%s_is_const:reg1_t==0:reg1_t | %s_val:reg64_t>=\$0x%Lx:reg64_t",$n,$n,$const_lb);
	    $s2 = sprintf("%s_is_const:reg1_t==0:reg1_t | %s_val:reg64_t<=\$0x%Lx:reg64_t",$n,$n,$const_ub);
	}
	else {
	    $s1 = sprintf("%s_val:reg64_t>=\$0x%016x:reg64_t",$n,$const_lb);
	    $s2 = sprintf("%s_val:reg64_t<=\$0x%016x:reg64_t",$n,$const_ub);
	}
	push @const_bounds_ec, ("-extra-condition", $s1);
	push @const_bounds_ec, ("-extra-condition", $s2);
	#push @const_bounds_ec, ('-extra-condition '.$n.'_val:reg64_t<=$'.$const_ub.':reg64_t ');
    }
}

#print "const_bounds_ec = @const_bounds_ec\n";

sub get_store_bytes {
    my ($string_addr,$size) = (@_);
    my @ret = ();
    for (my $i = 0; $i < $size; $i++) {
	push @ret, "-store-byte";
	push @ret, sprintf("0x%x=0x0", ($string_addr + $i));
    }
    return @ret;
}

my @table_opts = ();
if ($table_treatment == 1) {
    push @table_opts, "-table-limit";
    push @table_opts, "12";
    push @table_opts, "-trace-tables";
    push @table_opts, "-max-table-store-num";
    push @table_opts, "10000000";
    #push @table_opts, "-no-table-store";
}

my @trace_verbose_opts = ();
if ($trace_verbose >= 1) {
    push @trace_verbose_opts, "-trace-sym-addr-details";
    push @trace_verbose_opts, "-trace-sym-addrs";
    push @trace_verbose_opts, "-trace-syscalls";
    push @trace_verbose_opts, "-trace-temps";
    push @trace_verbose_opts, "-trace-regions";
    push @trace_verbose_opts, "-trace-struct-adaptor";
    push @trace_verbose_opts, "-trace-binary-paths-bracketed";
    push @trace_verbose_opts, "-trace-offset-limit";
    push @trace_verbose_opts, "-trace-basic";
    push @trace_verbose_opts, "-trace-assigns";
}
if ($trace_verbose == 2) {
    push @trace_verbose_opts, "-trace-insns";
    push @trace_verbose_opts, "-trace-loads";
    push @trace_verbose_opts, "-trace-stores";
    push @trace_verbose_opts, "-trace-solver";
}
if ($trace_verbose == 2) {
    push @trace_verbose_opts, "-trace-registers";
    push @trace_verbose_opts, "-trace-stmts";
}

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt,$ret_adapt, $struct_adapt) = (@_);

    my @input_string_store_bytes = get_store_bytes ($input_string_addr, $max_conc_region_size);
    # this makes the first byte of the input string be symbolic instead of being zero-initialized
    splice(@input_string_store_bytes, 0, 2*$input_string_length);
    
    open(TESTS, ">ceinputs");
    my @vals = ();
    if ($mo_adapter == 1) {
	@vals = ($sane_addr, $input_string_addr, 1, 0, 0, 0);
    } 
    if ($mo_adapter == 0) {
	@vals = ($sane_addr, 1, $input_string_addr, 0, 0, 0);
    } 
    splice(@vals, 6);
    my $test_str = join(" ", map(sprintf("0x%x", $_), @vals));
    print TESTS $test_str, "\n";
    close TESTS;

    #print "checking arg-adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
    my @conc_adapt = ();
    for my $i (0 .. $#$adapt) {
	my($name, $ty, $fmt) = @{$fields[$i]};
	my $val = $adapt->[$i];
	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	push @conc_adapt, ("-extra-condition", $s);
    }
    my @conc_ret_adapt = ();
    for my $i (0 .. $#$ret_adapt) {
	my($name, $ty, $fmt) = @{$ret_fields[$i]};
	my $val = $ret_adapt->[$i];
	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	push @conc_ret_adapt, ("-extra-condition", $s);
    }
    my @conc_struct_adapt = ();
    for my $i (0 .. $#$struct_adapt) {
	my($name, $ty, $fmt) = @{$struct_fields[$i]};
	my $val = $struct_adapt->[$i];
	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	push @conc_struct_adapt, ("-extra-condition", $s);
    }
    reinitialize_synth_struct_opt(1);
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64",
		$bin,
		@solver_opts, "-fuzz-start-addr", $fuzz_start_addr,
		"-omit-pf-af",
		"-time-stats",
		"-trace-memory-snapshots",
		@table_opts,
		@trace_verbose_opts,
		#"-save-decision-tree-interval", 1,
		#"-trace-decision-tree",
                #"-narrow-bitwidth-cutoff","1",
		"-trace-conditions",
		"-trace-decisions",
		"-trace-solver",
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		@synth_opt, @conc_adapt, @const_bounds_ec,
		@synth_ret_opt, @conc_ret_adapt,
		@synth_struct_opt,@conc_struct_adapt,
		#"-disable-ce-cache",
		"-return-zero-missing-x64-syscalls",
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-region-limit", $region_limit,
		"-branch-preference", "$match_jne_addr:0",
		@input_string_store_bytes,
		"-trace-iterations", "-trace-assigns", 
		"-solve-final-pc", #"-trace-assigns-final-pc",
		"-trace-stopping",
		"-random-seed", int(rand(10000000)),
		"--", $bin, 0, 0, "g", "ceinputs");
    my @printable;
    for my $a (@args) {
	if ($a =~ /[\s|<>]/) {
	    push @printable, "'$a'";
	} else {
	    push @printable, $a;
	}
    }
    print "@printable\n";
    open(LOG, "-|", @args);
    my($matches, $fails) = (0, 0);
    my(@ce, $this_ce);
    my(@arg_to_regnum, @regnum_to_arg, @fuzzball_extra_args, @regnum_to_saneaddr);
    $this_ce = 0;
    my $f1_completed = 0;
    my(@region_contents);
    my(%ce_mem_bytes);
    $f1_completed_count = 0;
    $iteration_count = 0;
    while (<LOG>) {
	if ($_ eq "Match\n" ) {
	    $matches++;
	} elsif (/^Iteration (.*):$/) {
	    $f1_completed = 0;
	    @arg_to_regnum = (0) x $f1nargs;
	    @regnum_to_arg = (0) x ($f1nargs+1);
	    @regnum_to_saneaddr = (0) x ($f1nargs+1);
	    my @tmp_reg_arr;
	    @region_contents = ();
	    for my $i (1 .. $max_conc_region_size+1) { push @tmp_reg_arr, 0; }
	    for my $i (1 .. ($f1nargs+1)) { push @region_contents, [@tmp_reg_arr]; }
	    $iteration_count++;
	    for (my $i=$sane_addr; $i<$sane_addr+$max_conc_region_size; $i++) {
		$ce_mem_bytes{$i}=0;
	    }
	    for (my $i=$input_string_addr; $i<$input_string_addr+$input_string_length; $i++) {
		$ce_mem_bytes{$i}=0;
	    }
	} elsif ($_ eq "Completed f1\n") {
	    $f1_completed = 1;
	    $f1_completed_count++;
	} elsif (($_ eq "Mismatch\n") or 
		 (/^Stopping at null deref at (0x[0-9a-f]+)$/ and $f1_completed == 1) or
		 (/^Stopping at access to unsupported address at (0x[0-9a-f]+)$/ and $f1_completed == 1) or
		 (/^Stopping on disqualified path at (0x[0-9a-f]+)$/ and $f1_completed == 1) or 
		 (/^Disqualified path at (0x[0-9a-f]+)$/ and $f1_completed == 1)) {
	    $fails++;
	    $this_ce = 1;
	} elsif (/^Input vars: (.*)$/ and $this_ce) {
	    my $vars = $1;
	    @ce = (0) x $f1nargs;
	    for my $v (split(/ /, $vars)) {
		if ($v =~ /^([a-f])=(0x[0-9a-f]+)$/) {
		    my $index = ord($1) - ord("a");
		    $ce[$index] = hex $2;
		    if ($arg_to_regnum[$index] != 0) {
			$ce[$index] = $sane_addr;
			$regnum_to_saneaddr[$arg_to_regnum[$index]] = $sane_addr;
			$sane_addr = $sane_addr + $max_conc_region_size;
		    }
		} elsif ($v =~ /^mem_byte_0x([0-9a-f]+)=(0x[0-9a-f]+)$/) { # mem_byte_0x42420000=0x1
		    $ce_mem_bytes{(hex $1)} = hex $2;
		}
	    }
	    for my $v (split (/ /, $vars)) {
		if($v =~ /^region_([0-9]+)_byte_0x([0-9a-f]+)=(0x[0-9a-f]+)$/) {
		    print "region assignment $1 $2 $3 for arg $regnum_to_arg[$1]\n";
		    # $1 -> region number
		    # $2 -> offset within region
		    # $3 -> value to be set
		    my $this_reg_byte = hex $2;
		    if($regnum_to_saneaddr[$1] != 0) {
			$region_contents[$1][$this_reg_byte+1]=$3;
		    }
		}
	    }
	    for my $i (1 .. $#region_contents) {
		for my $j (1 .. $#{$region_contents[$i]}) {
		    if($region_contents[$i][0] == 1) {
			push @fuzzball_extra_args, "-store-byte";
			push @fuzzball_extra_args, 
			sprintf("0x%x=%s", $regnum_to_saneaddr[$i]+$j-1, $region_contents[$i][$j]);
		    }
		}
	    }
	    $this_ce = 0;
	    print "  $_";
	    last;
	} elsif (/Address [a-f]_([0-9])+:reg64_t is region ([0-9]+)/ and $f1_completed == 0 ) {
	    my $add_line = $_;
	    my $add_var = -1;
	    for my $v (split(/ /, $add_line)) {
		if ($v =~ /^[a-f]_([0-9]+):reg64_t$/) { # matches argument name
		    $add_var = ord($v) - ord('a');
		} elsif ($v =~ /^[0-9]+$/) { # matches region number
		    if ($add_var < $f1nargs and $add_var >= 0) {
			$arg_to_regnum[$add_var] = int($v);
			$regnum_to_arg[int($v)]=$add_var;
			# 1 indicates symbolic input created a region
			$region_contents[$v][0]=1;
			print "Found region $v";
		    }
		}
	    }
	}
	print "  $_";
    }
    close LOG;

    for my $addr (sort (keys %ce_mem_bytes)) {
	push @fuzzball_extra_args, "-store-byte";
	push @fuzzball_extra_args,
	sprintf("0x%x=0x%x", $addr, $ce_mem_bytes{$addr});
	#printf("found memory assignment in CE search: $addr = $ce_mem_bytes{$addr}\n");
    }
    push @fuzzball_extra_args, @input_string_store_bytes;
    
    #push @fuzzball_extra_args, "-store-byte";
    #push @fuzzball_extra_args,sprintf("0x%x=0x%x", $input_string_addr, $key_const_val);
	
    $ce[0]=$sane_addr;
    if ($mo_adapter == 1) { 
	$ce[1]=$input_string_addr;
	$ce[2]=1;
    } 
    if ($mo_adapter == 0) {
	$ce[2]=$input_string_addr;
	$ce[1]=1;
    }
    $sane_addr = $sane_addr + $max_conc_region_size;
    $input_string_addr += 2*$max_conc_region_size;

    if ($matches == 0 and $fails == 0) {
	die "Missing results from check run";
    }
    if ($fails == 0) {
	return 1;
    } else {
	return (0, [@ce], [@fuzzball_extra_args]);
    }
}

# Given a set of tests, run with the adaptor symbolic to see if we can
# synthesize an adaptor that works for those tests.
sub try_synth {
    my($testsr, $_fuzzball_extra_args) = @_;
    printf("Trying to synthesize with sane_addr=0x%x\n", $sane_addr);
    my @fuzzball_extra_args = @{ $_fuzzball_extra_args };
    # foreach my $i (0 .. $#fuzzball_extra_args) {
    # 	print "fuzzball_extra_args: fuzzball_extra_args[$i]= $fuzzball_extra_args[$i]\n";
    # }
    open(TESTS, ">tests");
    for my $t (@$testsr) {
	my @vals = (@$t, (0) x 6);
	splice(@vals, 6);
	my $test_str = join(" ", map(sprintf("0x%x", $_), @vals));
	print TESTS $test_str, "\n";
    }
    close TESTS;
    reinitialize_synth_struct_opt(0);

    #     my $adapt = [0, 0, 0, 2, 0, 1]; 
    #     my $ret_adapt = [0, 0];
    #     #my $struct_adapt = [0x70001, 0x4, 0x2, 0x8000f0001, 0x1, 0x2]; #(type, size, n) for om
    #     my $struct_adapt = [0x70001, 0x4, 0x2, 0x8000b0001, 0x4, 0x4]; #(type, size, n) for mo
    #     my @conc_adapt = ();
    #     for my $i (0 .. $#$adapt) {
    #     	my($name, $ty, $fmt) = @{$fields[$i]};
    #     	my $val = $adapt->[$i];
    #     	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
    #     	push @conc_adapt, ("-extra-condition", $s);
    #     }
    #     my @conc_ret_adapt = ();
    #     for my $i (0 .. $#$ret_adapt) {
    #     	my($name, $ty, $fmt) = @{$ret_fields[$i]};
    #     	my $val = $ret_adapt->[$i];
    #     	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
    #     	push @conc_ret_adapt, ("-extra-condition", $s);
    #     }
    #     my @conc_struct_adapt = ();
    #     for my $i (0 .. $#$struct_adapt) {
    #     	my($name, $ty, $fmt) = @{$struct_fields[$i]};
    #     	my $val = $struct_adapt->[$i];
    #     	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
    #     	push @conc_struct_adapt, ("-extra-condition", $s);
    #     }
    
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64", $bin,
		@solver_opts, 
		"-fuzz-start-addr", $fuzz_start_addr,
		#tell FuzzBALL to run in adaptor search mode, FuzzBALL will run in
		#counter example search mode otherwise
		"-adaptor-search-mode",
		"-trace-iterations", 
		"-solve-final-pc", "-trace-assigns-final-pc",
		@table_opts,
		@trace_verbose_opts,
		"-return-zero-missing-x64-syscalls",
		#"-disable-ce-cache",
		@synth_opt, @const_bounds_ec,
		@synth_ret_opt,
		@synth_struct_opt,
		# these next 3 lines go along with the concrete adapter setup above
		#     @synth_opt, @conc_adapt, @const_bounds_ec,
		#     @synth_ret_opt, @conc_ret_adapt,
		#     @synth_struct_opt,@conc_struct_adapt,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		"-branch-preference", "$match_jne_addr:1",
		"-trace-conditions", "-omit-pf-af",
		"-time-stats",
		#"-trace-decision-tree",
		#"-save-decision-tree-interval","1",
		"-trace-decisions",
		"-trace-stopping",
		"-trace-memory-snapshots",
		#"-zero-memory", #dont use zero memory because adapter bytes are symbolic inputs, input and output string bytes are zero-initialized separately except for the first $input_string_length bytes at $input_string_addr
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-f2-limit", $iteration_f2_limit,
		@fuzzball_extra_args,
		"-region-limit", $region_limit,
		"-random-seed", int(rand(10000000)),
		"--", $bin, 0, 0, "f", "tests");
    #print "@args\n";
    my @printable;
    for my $a (@args) {
	if ($a =~ /[\s|<>]/) {
	    push @printable, "'$a'";
	} else {
	    push @printable, $a;
	}
    }
    print "@printable\n";
    open(LOG, "-|", @args);
    my($success, %fields);
    $success = 0;
    while (<LOG>) {
	if ($_ eq "All tests succeeded!\n") {
	    $success = 1;
	} elsif (/^Disqualified path at (0x[0-9a-f]+)$/) {
	    $success = 0;
	} elsif (/^Input vars: (.*)$/ and $success) {
	    my $vars = $1;
	    %fields = ();
	    for my $v (split(/ /, $vars)) {
		$v =~ /^(\w+)=(0x[0-9a-f]+)$/
		  or die "Parse failure on variable assignment <$v>";
		$fields{$1} = hex $2;
	    }
	    print "  $_";
	    last;
	}
	print "  $_" unless /^Input vars:/;
    }
    close LOG;
    if (!$success) {
	print "Synthesis failure: seems the functions are not equivalent.\n";
	exit 2;
    }
    my @afields;
    my @bfields;
    my @cfields;
    for my $fr (@fields) {
	push @afields, $fields{$fr->[0]};
    }
    for my $fr (@ret_fields) {
	push @bfields, $fields{$fr->[0]};
    }
    for my $fr (@struct_fields) {
	push @cfields, $fields{$fr->[0]};
    }
    return ([@afields], [@bfields], [@cfields]);
}

# Set these to test a specific adaptor
#  $adapt->[0]=0;
#  $adapt->[1]=0;
#  $adapt->[2]=1;
#  $adapt->[3]=0;
#  $adapt->[4]=1;
#  $adapt->[5]=10;

# Main loop: starting with a stupid adaptor and no tests, alternate
# between test generation and synthesis.
my $adapt = [(0) x @fields];
my $ret_adapt = [(0) x @ret_fields];
my $struct_adapt = [(0) x @struct_fields];
# type, size, number of array entries
for(my $i=0; $i< $n_fields; $i++) {
    $struct_adapt->[$i*3] = (($i*4)<<32)+(((($i+1)*4)-1)<<16);
    $struct_adapt->[$i*3+1] = 4;
    $struct_adapt->[$i*3+2] = 1;
}

# Setting up the default adaptor to be the identity adaptor
if ($default_adaptor_pref == 1) {
    my $f1_narg_counter=0;
    for my $i (0 .. $#$adapt) {
	if ($i%2 == 1) {
	    $adapt->[$i] = $f1_narg_counter;
	    if ($f1_narg_counter < $f1nargs-1) {
		$f1_narg_counter= $f1_narg_counter + 1;
	    }
	}
    }
}


# If outer function takes no arguments, then the inner function can only use constants
if ($f1nargs==0) {
    for my $i (0 .. $#$adapt) {
	if ($i%2 == 0) { # X_is_const field
	    $adapt->[$i] = 1;
	    $adapt->[$i+1] = 1;
	}
    }
}

# my $adapt = [0, 0, 0, 2, 0, 1]; 
# my $ret_adapt = [0, 0];
# my $struct_adapt = [0x70001, 0x4, 0x2, 0x800170001, 0x1, 0x4]; #(type, size, n) for om
# my $adapt = [0, 0, 0, 2, 0, 1]; 
# my $ret_adapt = [0, 0];
# #my $struct_adapt = [0x70001, 0x4, 0x2, 0x800170001, 0x1, 0x4]; #(type, size, n) for om
# my $struct_adapt = [0x70001, 0x4, 0x2, 0x8000b0001, 0x4, 0x4]; #(type, size, n) for mo
sub get_struct_adapt_str () {
    my $tmp_str="";
    for(my $i=0; $i<=$#struct_fields; $i++) {
	my($name, $ty, $fmt) = @{$struct_fields[$i]};
	$tmp_str=$tmp_str.sprintf("%s=0x".$fmt, $name, $struct_adapt->[$i]).", ";
    }
    return $tmp_str;
}

print "default adaptor = @$adapt ret-adaptor = @$ret_adapt structure-adaptor = @$struct_adapt\n";
my @tests = ();
my $done = 0;
my $start_time = time();
my $reset_time = time();
my $diff;
my $diff1;
while (!$done) {
    my $adapt_s = join(",", @$adapt);
    my $ret_adapt_s = join(",", @$ret_adapt);
    printf "Checking simple adaptor = $adapt_s, ret adaptor = $ret_adapt_s, ".
	"struct adaptor = ".get_struct_adapt_str()." with sane_addr=0x%x\n",$sane_addr;
	#"struct adaptor = 0x%x,0x%x,%d,%d:\n",
	#    $struct_adapt->[0], $struct_adapt->[1], $struct_adapt->[2], $struct_adapt->[3];
    my($res, $cer, $_fuzzball_extra_args) = check_adaptor($adapt, $ret_adapt, $struct_adapt);
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last CE search time = $diff1\n";
    $reset_time = time();
    if ($res) {
	print "Success!\n";
	print "Final test set:\n";
	for my $tr (@tests) {
	    print " $tr->[0], $tr->[1]\n";
	}
	my $verified="partial";
	if ($f1_completed_count == $iteration_count) {
	    $verified="complete";
	}
	printf "Final adaptors: arg=$adapt_s, ret=$ret_adapt_s, ".
	    "struct=%s with $f1_completed_count,$iteration_count,$verified\n", 
	    get_struct_adapt_str();
	$done = 1;
	last;
    } else {
	push @fuzzball_extra_args_arr, @{ $_fuzzball_extra_args };
	my $ce_s = join(", ", @$cer);
	print "Mismatch on input $ce_s; adding as test\n";
	push @tests, [@$cer];
    }

    ($adapt, $ret_adapt, $struct_adapt) = try_synth(\@tests, \@fuzzball_extra_args_arr);
    print "Synthesized arg adaptor ".join(",",@$adapt).
	" and return adaptor ".join(",",@$ret_adapt).
	" and struct adaptor ".get_struct_adapt_str()."\n";
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last AS search time = $diff1\n";
    $reset_time = time();
}
