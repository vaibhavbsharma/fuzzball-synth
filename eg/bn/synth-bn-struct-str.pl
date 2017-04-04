#!/usr/bin/perl

use strict;

$| = 1;

die "Usage: synth-one.pl <f1num> <f2num> <seed> <default adaptor(0=zero,1=identity) [<lower bound for constant> <upper bound for constant>]"
  unless @ARGV == 6;
my($f1num, $f2num, $rand_seed, $default_adaptor_pref, $const_lb, $const_ub) = @ARGV;

srand($rand_seed);
my $unused_1=`ulimit -s unlimited`;
die "failed to set ulimit" unless $unused_1== 0;
# Configurables
my $split_target_formulas=1;
my $path_depth_limit = 100;
my $iteration_limit = 4000;

my $adaptor_ivc = 1;

my $t_n_fields = 5;
my $i_n_fields = 3;
my $starting_sane_addr = 0x42420000;
my $max_struct_size=32;

my $max_steps = 1000;
my $key_const_val = 102;
my $str_len=32;
# End configurables

my $sane_addr = $starting_sane_addr;
my $string_addr = $starting_sane_addr + $max_struct_size*$max_steps;
my $starting_string_addr = $string_addr;
my $max_conc_region_size = $max_struct_size;
my $region_limit = $max_conc_region_size;
my @fuzzball_extra_args_arr;

# Paths to binaries: these probably differ on your system. You can add
# your locations to the list, or set the environment variable.
my $fuzzball="fuzzball";
my $stp="stp";
my $f1_completed_count = 0;
my $iteration_count = 0;

my $bin = "./bn-struct-str";

print "compiling binary: ";
my $unused = ` gcc -static -m64 -fno-jump-tables bn-struct-str.c  -I /export/scratch/vaibhav/mbedtls-2.3.0/include/  -g -o bn-struct-str /export/scratch/vaibhav/openssl/libcrypto.a /export/scratch/vaibhav/mbedtls-2.3.0/library/libmbedcrypto.a  -ldl -lpthread   -std=c99`;
my $gcc_ec = $?;
die "failed to compile $bin" unless $gcc_ec == 0;
print "gcc_ec = $gcc_ec\n";

my @func_info;
open(F, "<types-no-float-1204.lst") or die;
while (<F>) {
    my($num, $nargs, $name, $type) = split(" ", $_, 4);
    if ($nargs =~ /\+/) {
	$nargs = substr($nargs,0,1);
    }
    push @func_info, [$num, $nargs, $name, $type];
}
close F;

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
printf "%d = %s(%d)\n", $f1num, $func_info[$f1num][2], $func_info[$f1num][1];
printf "%d = %s(%d)\n", $f2num, $func_info[$f2num][2], $func_info[$f2num][1];

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
for (my $i =1; $i <= $i_n_fields; $i++) {
    my $f_type_str = sprintf("f%d_type", $i);
    my $field_size_str = sprintf("f%d_size", $i);
    my $field_n_str = sprintf("f%d_n", $i);
    my $m_str = sprintf("m%d_arith", $i);
    my $c_str = sprintf("c%d_arith", $i);
    push @struct_fields, [$f_type_str, "reg64_t", "%01x"];
    push @struct_fields, [$field_size_str, "reg16_t", "%01x"];
    push @struct_fields, [$field_n_str, "reg16_t", "%01x"];
    push @struct_fields, [$m_str, "reg64_t", "%01x"];
    push @struct_fields, [$c_str, "reg64_t", "%01x"];
}


my($f1nargs, $f2nargs) = ($func_info[$f1num][1], $func_info[$f2num][1]);
#$f1nargs=6;
#$f2nargs=6;
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

my @str_ce = ();
sub reinitialize_str_ce {
    @str_ce = ();
    my $steps = ($string_addr - $starting_string_addr)/($str_len+1);
    for(my $off=0; $off < $steps; $off++) {
	my $string_base = $starting_string_addr + ($off*$str_len);
	for(my $i=1; $i<$str_len-1; $i++) {
	    push @str_ce, "-store-byte";
	    push @str_ce, sprintf("0x%x=0x%x", $string_base+$i, $key_const_val);
	}
	push @str_ce, "-store-byte";
	push @str_ce, sprintf("0x%x=0x0", $string_base+$str_len);
    }
}

sub reinitialize_synth_struct_opt  {
    my($is_ce) = (@_);
    my $steps = ($sane_addr - $starting_sane_addr)/$max_conc_region_size;
    @synth_struct_opt = ();
    if( $is_ce == 0) {
	for (my $s=0; $s < $steps; $s++ ) {
	    push @synth_struct_opt, "-synthesize-struct-adaptor";
	    my $tmp_str;
	    if ($s < $steps) {
		my $this_addr = ($starting_sane_addr + ($s * $max_conc_region_size));
		push @synth_struct_opt, sprintf("0x%x", $this_addr );
	    }
	}
    } else {
	push @synth_struct_opt, "-synthesize-struct-adaptor";
	push @synth_struct_opt, $sane_addr;
	my @tmp_arr = ("-store-long", sprintf("0x%x=0x0", $sane_addr),
		       "-store-long", sprintf("0x%x=0x0", $sane_addr+8),
		       "-store-word", sprintf("0x%x=0x0", $sane_addr+16),
		       "-store-word", sprintf("0x%x=0x1", $sane_addr+20));
	push (@synth_struct_opt, @tmp_arr);
    }
    push @synth_struct_opt, "-struct-adaptor-params";
    push @synth_struct_opt, sprintf("%d:%d:%d", $t_n_fields, $i_n_fields, $max_struct_size);
    if($split_target_formulas==1) {
	push @synth_struct_opt, "-split-target-formulas";
    }
    if($adaptor_ivc==1) {
	push @synth_struct_opt, "-adaptor-ivc";
    }
   for my $i (0 ..  $#synth_struct_opt) {
    	print "synth_struct_opt[$i] = $synth_struct_opt[$i]\n";
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
    my $s1='';
    my $s2='';
    my $s3='';
    my $s4='';
    for (my $i=1; $i<=$i_n_fields; $i++) {
	$s1 = sprintf("m%d_arith:reg64_t>=\$0x%016x:reg64_t",$i,$const_lb);
	$s2 = sprintf("m%d_arith:reg64_t<=\$0x%016x:reg64_t",$i,$const_ub);
	$s3 = sprintf("c%d_arith:reg64_t>=\$0x%016x:reg64_t",$i,$const_lb);
	$s4 = sprintf("c%d_arith:reg64_t<=\$0x%016x:reg64_t",$i,$const_ub);
	push @const_bounds_ec, ("-extra-condition", $s1);
	push @const_bounds_ec, ("-extra-condition", $s2);
	push @const_bounds_ec, ("-extra-condition", $s3);
	push @const_bounds_ec, ("-extra-condition", $s4);
    }
}

#print "const_bounds_ec = @const_bounds_ec\n";

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt,$ret_adapt, $struct_adapt) = (@_);

    open(TESTS, ">ceinputs");
    my @vals = ($sane_addr, $string_addr, 0, 0, 0, 0);
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
    my @tmp_str = ();
    for(my $i=1; $i<$str_len-1; $i++) {
	push @tmp_str, "-store-byte";
	push @tmp_str, sprintf("0x%x=0x%x", $string_addr+$i, $key_const_val);
    }
    # first character can be - or f
    push @tmp_str, "-extra-condition";
    my $s = sprintf("mem[0x%x:reg32_t]:reg8_t==0x2d:reg8_t | mem[0x%x:reg32_t]:reg8_t==0x%x:reg8_t", $string_addr, $string_addr, $key_const_val);
    push @tmp_str, $s;
    # last character can be \0 (the null byte) or f
    push @tmp_str, "-extra-condition";
    my $s = sprintf("mem[0x%x:reg32_t]:reg8_t==0x0:reg8_t | mem[0x%x:reg32_t]:reg8_t==0x%x:reg8_t", $string_addr+$str_len-1, $string_addr+$str_len-1, $key_const_val);
    push @tmp_str, $s;
    push @tmp_str, "-store-byte";
    push @tmp_str, sprintf("0x%x=0x0", $string_addr+$str_len);
    
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64",
		$bin,
		@solver_opts, "-fuzz-start-addr", $fuzz_start_addr,
		"-trace-sym-addr-details",
		"-trace-sym-addrs",
		"-trace-syscalls",
		"-omit-pf-af",
		"-trace-temps",
		"-trace-regions",
		"-trace-struct-adaptor",
		"-time-stats",
		"-trace-memory-snapshots",
		"-trace-tables",
		"-table-limit","12",
		#"-save-decision-tree-interval", 1,
		#"-trace-decision-tree",
		"-trace-binary-paths-bracketed",
                #"-narrow-bitwidth-cutoff","1",
		#"-trace-offset-limit",
		"-trace-basic",
		#"-trace-eip",
		#"-trace-registers",
		#"-trace-stmts",
		#"-trace-insns",
		#"-trace-loads",
		#"-trace-stores",
		"-trace-conditions",
		"-trace-decisions",
		#"-trace-solver",
		@tmp_str,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		@synth_opt, @conc_adapt, @const_bounds_ec,
		@synth_ret_opt, @conc_ret_adapt,
		@synth_struct_opt,@conc_struct_adapt, 
		"-disable-ce-cache",
		"-return-zero-missing-x64-syscalls",
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-region-limit", $region_limit,
		"-branch-preference", "$match_jne_addr:0",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-trace-stopping",
		"-random-seed", int(rand(10000000)),
		"--", $bin, $f1num, $f2num, "g", "ceinputs");
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
	    # needed to capture the concretized value of the last byte in input string
	    $ce_mem_bytes{$string_addr+$str_len-1}=0;
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

    for my $addr (keys %ce_mem_bytes) {
	push @fuzzball_extra_args, "-store-byte";
	push @fuzzball_extra_args,
	sprintf("0x%x=0x%x", $addr, $ce_mem_bytes{$addr});
	#printf("found memory assignment in CE search: 0x%x = $ce_mem_bytes{$addr}\n", $addr);
    }
    
    $ce[0]=$sane_addr;
    $ce[1]=$string_addr;
    $sane_addr = $sane_addr + $max_conc_region_size;
    $string_addr = $string_addr + $str_len + 1;

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
    reinitialize_str_ce();
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64", $bin,
		@solver_opts, 
		"-fuzz-start-addr", $fuzz_start_addr,
		"-trace-temps",
		#tell FuzzBALL to run in adaptor search mode, FuzzBALL will run in
		#counter example search mode otherwise
		"-adaptor-search-mode",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-table-limit","12",
		"-return-zero-missing-x64-syscalls",
		#"-disable-ce-cache",
		@synth_opt, @const_bounds_ec,
		@synth_ret_opt,
		@synth_struct_opt,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		"-branch-preference", "$match_jne_addr:1",
		"-no-fail-on-huer",
		"-trace-conditions", "-omit-pf-af",
		"-trace-syscalls",
		"-trace-struct-adaptor",
		"-time-stats",
		#"-trace-decision-tree",
		#"-save-decision-tree-interval","1",
		"-trace-decisions",
		"-trace-stopping",
		"-trace-regions",
		"-trace-binary-paths-bracketed",
		"-trace-memory-snapshots",
		"-trace-sym-addr-details",
		"-trace-sym-addrs",
		"-trace-tables",
		# "-trace-offset-limit",
		"-trace-basic",
		#"-trace-eip",
		#"-trace-registers",
		#"-trace-stmts",
		# "-trace-insns",
		#"-trace-loads",
		#"-trace-stores",
		#"-trace-solver",
		"-zero-memory",
		@fuzzball_extra_args,
		@str_ce,
		"-region-limit", $region_limit,
		"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-random-seed", int(rand(10000000)),
		"--", $bin, $f1num, $f2num, "f", "tests");
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
    my @dfields;
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
for(my $i=0; $i< $i_n_fields; $i++) {
    $struct_adapt->[$i*5] = (($i*4)<<32)+(((($i+1)*4)-1)<<16);
    $struct_adapt->[$i*5+1] = 4;
    $struct_adapt->[$i*5+2] = 1;
    $struct_adapt->[$i*5+3] = 1;
    $struct_adapt->[$i*5+4] = 0;
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

# $adapt = [0, 0, 0, 1, 0, 1]; 
# $ret_adapt = [0, 0];
# $struct_adapt = [0x1000130001, 0x4, 0x1, 0xc000f0001, 0x8, 0x1, 0x70001, 0x8, 0x1];

# If outer function takes no arguments, then the inner function can only use constants
if ($f1nargs==0) {
    for my $i (0 .. $#$adapt) {
	if ($i%2 == 0) { # X_is_const field
	    $adapt->[$i] = 1;
	    $adapt->[$i+1] = 1;
	}
    }
}

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
	    "struct=%s, with $f1_completed_count,$iteration_count,$verified\n", 
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
