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
my $path_depth_limit = 300;
my $iteration_limit = 100000000;

my $adaptor_ivc = 1;
my $str_len=1;
my $starting_sane_addr = 0x42420000;

my $max_steps = 1000;
my $key_const_val = 97;
my $N = $str_len;
# End configurables

my $max_matrix_size=$str_len+1; # 1st row for addrs, N rows, N cols
my $sane_addr = $starting_sane_addr;
my ($a_addr, $b_addr, $c_addr);
my (@a_addrs, @b_addrs, @c_addrs);
my $max_conc_region_size = $max_matrix_size;
my $region_limit = $max_conc_region_size;
my @fuzzball_extra_args_arr;

my $fuzzball = "../bin/fuzzball";
# my $stp = "../bin/stp-old-dynamic";
my $stp = "../bin/stp";
# my $stp = "/export/scratch/vaibhav/fuzzball-adaptorsynth/stp/stp-lateststp";

my $f1_completed_count = 0;
my $iteration_count = 0;

my $bin = "./obfs_clone2";

# print "compiling binary: ";
# my $unused = `/export/scratch/xxxxxxx/obfs_build/bin/clang -static $bin.c -o $bin`;
# #my $unused = `gcc -static $bin.c -g -o $bin `;
# my $gcc_ec = $?;
# die "failed to compile $bin" unless $gcc_ec == 0;

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

sub reinitialize_matrix_addrs {
    $a_addr = $sane_addr;
    $b_addr = $a_addr + $max_matrix_size;
    $c_addr = $b_addr + $max_matrix_size;
    @a_addrs = @b_addrs = @c_addrs = ();
    my $steps = ($sane_addr - $starting_sane_addr)/$max_conc_region_size;
    for my $i (0 .. $steps) {
	for my $j (0 .. $str_len-1) {
	    push @a_addrs, "-store-byte";
	    push @a_addrs,
	    sprintf("0x%x=0x%x", $starting_sane_addr + $max_conc_region_size*$i + $j, $key_const_val + $i);
	}
    }
}
 
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

my @arg_addr;
for my $i (0 .. 5) {
    $arg_addr[$i] =
      "0x" . substr(`nm $bin | fgrep " B global_arg$i"`, 0, 16);
}

my $match_jne_addr =
  "0x" . substr(`objdump -dr $bin | grep 'jne.*compare+'`, 2, 6);

print "$fuzzball\n";
print "$stp\n";
print "fuzz-start-addr : $fuzz_start_addr\n";
print "f1:   $f1_addr @ $f1_call_addr\n";
print "f2:   $f2_addr\n";
print "wrap_f2: $wrap_f2_addr @ $f2_call_addr\n";
for my $i (0 .. 5) {
    print "arg$i: $arg_addr[$i]\n";
}
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

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt,$ret_adapt) = (@_);

    open(TESTS, ">ceinputs");
    reinitialize_matrix_addrs();
    my @vals = ($a_addr, $str_len, 0, 0, 0, 0);
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
    # my @str;
    # for my $i (0 .. $str_len-1) {
    # 	my $tmp_addr = $a_addr + $i;
    # 	push @str, "-store-byte";
    # 	push @str, sprintf("0x%x=0x%x", $tmp_addr, $key_const_val);
    # }
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64",
		$bin,
		@solver_opts, "-fuzz-start-addr", $fuzz_start_addr,
		"-symbolic-long", "$arg_addr[0]=a",
		"-symbolic-long", "$arg_addr[1]=b",
		"-symbolic-long", "$arg_addr[2]=c",
		"-symbolic-long", "$arg_addr[3]=d",
		"-symbolic-long", "$arg_addr[4]=e",
		"-symbolic-long", "$arg_addr[5]=f",
		"-trace-sym-addr-details",
		"-trace-sym-addrs",
		"-trace-syscalls",
		"-omit-pf-af",
		"-trace-temps",
		"-trace-regions",
		# "-time-stats",
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
		# "-trace-registers",
		#"-trace-stmts",
		# "-trace-insns",
		# "-trace-loads",
		# "-trace-stores",
		"-trace-conditions",
		"-trace-decisions",
		#"-trace-solver",
		# @str, #"-store-byte", $tmp_str,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		@a_addrs, #@b_addrs, @c_addrs,
		@synth_opt, @conc_adapt, @const_bounds_ec,
		@synth_ret_opt, @conc_ret_adapt,
		"-disable-ce-cache",
		"-return-zero-missing-x64-syscalls",
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-dont-compare-linux-syscalls",
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
	    for (my $i=$a_addr+4*$N; $i<$a_addr+$max_matrix_size; $i++) {
		$ce_mem_bytes{$i}=0;
	    }
	    for (my $i=$b_addr+4*$N; $i<$b_addr+$max_matrix_size; $i++) {
		$ce_mem_bytes{$i}=0;
	    }
	    for (my $i=$c_addr+4*$N; $i<$c_addr+$max_matrix_size; $i++) {
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

    for my $addr (keys %ce_mem_bytes) {
	push @fuzzball_extra_args, "-store-byte";
	push @fuzzball_extra_args,
	sprintf("0x%x=0x%x", $addr, $ce_mem_bytes{$addr});
	#printf("found memory assignment in CE search: $addr = $ce_mem_bytes{$addr}\n");
    }

    push @fuzzball_extra_args, @a_addrs;
    # push @fuzzball_extra_args, @b_addrs;
    # push @fuzzball_extra_args, @c_addrs;

    $ce[0]=$a_addr;
    $ce[1]=$str_len;
    $sane_addr = $sane_addr + $max_conc_region_size*3;

    #push @fuzzball_extra_args, "-store-byte";
    #push @fuzzball_extra_args,sprintf("0x%x=0x%x", $a_addr, $key_const_val);

    # for my $i (0 .. $str_len-1) {
    # 	my $tmp_addr = $a_addr + $i;
    # 	push @fuzzball_extra_args, "-store-byte";
    # 	push @fuzzball_extra_args, sprintf("0x%x=0x%x", $tmp_addr, $key_const_val);
    # }
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
		"-disable-ce-cache",
		@synth_opt, @const_bounds_ec,
		@synth_ret_opt,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		"-branch-preference", "$match_jne_addr:1",
		"-trace-conditions", "-omit-pf-af",
		"-trace-syscalls",
		# "-time-stats",
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
		#"-trace-offset-limit",
		"-trace-basic",
		#"-trace-eip",
		#"-trace-registers",
		#"-trace-stmts",
		#"-trace-insns",
		#"-trace-loads",
		#"-trace-stores",
		#"-trace-solver",
		"-zero-memory",
		@fuzzball_extra_args,
		"-region-limit", $region_limit,
		"-dont-compare-linux-syscalls",
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
    for my $fr (@fields) {
	push @afields, $fields{$fr->[0]};
    }
    for my $fr (@ret_fields) {
	push @bfields, $fields{$fr->[0]};
    }
    return ([@afields], [@bfields]);
}

# Main loop: starting with a stupid adaptor and no tests, alternate
# between test generation and synthesis.
my $adapt = [(0) x @fields];
my $ret_adapt = [(0) x @ret_fields];

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

$adapt=[0,0, 0,0, 0,1, 1,0, 1,0, 1,0];
$ret_adapt = [0, 0];

print "default adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
my @tests = ();
my $done = 0;
my $start_time = time();
my $reset_time = time();
my $diff;
my $diff1;
while (!$done) {
    my $adapt_s = join(",", @$adapt);
    my $ret_adapt_s = join(",", @$ret_adapt);
    printf "Checking simple adaptor = $adapt_s, ret adaptor = $ret_adapt_s\n";
    my($res, $cer, $_fuzzball_extra_args) = check_adaptor($adapt, $ret_adapt);
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
	    "with $f1_completed_count,$iteration_count,$verified\n";
	$done = 1;
	last;
    } else {
	push @fuzzball_extra_args_arr, @{ $_fuzzball_extra_args };
	# my $ce_s = join(", ", @$cer);
	my $ce_s = join(", ", map(sprintf("0x%x", $_), @$cer));
	print "Mismatch on input $ce_s; adding as test\n";
	push @tests, [@$cer];
    }

    ($adapt, $ret_adapt) = try_synth(\@tests, \@fuzzball_extra_args_arr);
    print "Synthesized arg adaptor ".join(",",@$adapt).
	" and return adaptor ".join(",",@$ret_adapt)."\n";
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last AS search time = $diff1\n";
    $reset_time = time();
}
