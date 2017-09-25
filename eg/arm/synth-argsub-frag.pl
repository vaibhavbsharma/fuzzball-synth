#!/usr/bin/perl

use strict;

die "Usage: synth-one.pl <f1num> <f2num> <seed> <default adaptor(0=zero,1=identity) <constant bounds file> (0=x64,any other val=arm) <fragment file name>"
  unless @ARGV == 7;
my($f1num, $f2num, $rand_seed, $default_adaptor_pref, $const_bounds_file, $arch_flag, $frag_file_name) = @ARGV;

srand($rand_seed);

my $arch_str = "";
if ($arch_flag==0) {
    $arch_str="x64"; 
} else {
    $arch_str="arm"; 
} 

my $path_depth_limit = 300;
my $iteration_limit = 4000;

my $region_limit = 936;

my $sane_addr = 0x42420000;

my @fuzzball_extra_args_arr;

# Paths to binaries: these probably differ on your system. You can add
# your locations to the list, or set the environment variable.
my $fuzzball="fuzzball";
my $stp="stp";

my $f1_completed_count = 0;
my $iteration_count = 0;

my $bin = "./test_" . $arch_str;

if ($arch_flag==0) {
    print "compiling adaptor search binary: ";
    my $unused = `gcc -static $bin.c -g -o $bin -lpthread`;
    my $gcc_ec = $?;
    die "failed to compile $bin" unless $gcc_ec == 0;
    print "gcc_ec = $gcc_ec\n";
}

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

my $fuzz_start_addr = "0x" . substr(`nm $bin | fgrep "T fuzz_start"`, 0, 8);

my $f1_addr = "0x" . substr(`nm $bin | egrep -e 'T f1'`, 0, 8);

my $f1_call_addr;
if ($arch_flag == 0 ) {
  $f1_call_addr = "0x" . substr(`objdump -dr $bin | grep 'call.*<f1>'`, 2, 6);
} else {
  $f1_call_addr = "0x" . substr(`objdump -dr $bin | egrep -e 'bl.*<f1>'`, 4, 4);
}

my $f2_addr = "0x" . substr(`nm $bin | egrep -e 'T f2'`, 0, 8);

my $wrap_f2_addr = "0x" . substr(`nm $bin | fgrep " T wrap_f2"`, 0, 8);

my $f2_call_addr;
if ($arch_flag == 0) {
  $f2_call_addr = "0x" . substr(`objdump -dr $bin | grep 'call.*<wrap_f2>'`, 2, 6);
} else {
  $f2_call_addr = "0x" . substr(`objdump -dr $bin | egrep -e 'bl.*<f2>'`, 4, 4);
}

my $post_f1_call = sprintf("0x%x",hex($f1_call_addr)+0x4);
my $post_f2_call = sprintf("0x%x",hex($f2_call_addr)+0x4);

my @arg_addr;
for my $i (0 .. 12) {
    $arg_addr[$i] =
      "0x" . substr(`nm $bin | egrep -e " B global_arg$i\$"`, 0, 8);
}

my $match_jne_addr;
if ($arch_flag == 0) {
  $match_jne_addr = "0x" . substr(`objdump -dr $bin | grep 'jne.*compare+'`, 2, 6);
} else { 
  $match_jne_addr = "0x" . substr(`objdump -dr $bin | grep 'bne.*compare+'`, 4, 4);
}

print "$fuzzball\n";
print "$stp\n";
print "fuzz-start-addr: $fuzz_start_addr\n";
print "f1:   $f1_addr @ $f1_call_addr\n";
print "f2:   $f2_addr\n";
print "wrap_f2: $wrap_f2_addr @ $f2_call_addr\n";
for my $i (0 .. 12) {
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
   ["a_val",      "reg32_t", "%016x"],
   ["b_is_const",  "reg1_t", "%01x"],
   ["b_val",      "reg32_t", "%016x"],
   ["c_is_const",  "reg1_t", "%01x"],
   ["c_val",      "reg32_t", "%016x"],
   ["d_is_const",  "reg1_t", "%01x"],
   ["d_val",      "reg32_t", "%016x"],
   ["e_is_const",  "reg1_t", "%01x"],
   ["e_val",      "reg32_t", "%016x"],
   ["f_is_const",  "reg1_t", "%01x"],
   ["f_val",      "reg32_t", "%016x"],
);

my @ret_fields = 
(
   ["ret_type",  "reg8_t", "%01x"],
   ["ret_val",   "reg32_t", "%016x"],
);

my($f1nargs, $f2nargs) = ($func_info[$f1num][1], $func_info[$f2num][1]);
#$f1nargs=6;
#$f2nargs=6;

splice(@fields, 2 * $f2nargs);

my @solver_opts = ("-solver", "smtlib", 
		   # "-save-solver-files", 
		   "-solver-path", $stp, 
		   # "-solver-timeout",5,"-timeout-as-unsat"
    );

my @synth_opt = ("-synthesize-adaptor",
		 join(":", "simple", $f2_call_addr, $f1nargs, $f2_addr, $f2nargs));

my @synth_ret_opt = ("-synthesize-return-adaptor",
		 join(":", "return-typeconv", $f2_call_addr, $post_f2_call, $f2nargs));

print "synth_ret_opt = @synth_ret_opt\n";

open(F, "<$const_bounds_file") or die "cannot open constant bounds file";
my @const_bounds = ();
my @const_vals = ();
while(<F>) {
    if(/^.*-.*$/) {
	my @a = split /-/, $_;
	push @const_bounds, ($a[0], $a[1]);
    } else { 
	my $c = $_ + 0;
	push @const_vals, $c;
    }
}
if(scalar(@const_bounds)==0 && scalar(@const_vals)==0) {
    die "no constant bounds specified in $const_bounds_file";
}
my @const_bounds_ec = ();
for (my $i=0; $i<$f2nargs; $i++) {
    my $n = chr(97 + $i);
    my $s1 = sprintf("%s_is_const:reg1_t==0:reg1_t ", $n);
    my $s2 = sprintf("%s_is_const:reg1_t==0:reg1_t ", $n);
    if($f1nargs == 0) {
	$s1 = "1:reg1_t == 0:reg1_t";
	$s2 = "1:reg1_t == 0:reg1_t";
    }
    for (my $i=0; $i < scalar(@const_bounds); $i+=2) {
	$s1 .= sprintf(" | %s_val:reg32_t>=\$0x%Lx:reg32_t",$n,$const_bounds[$i]);
	$s2 .= sprintf(" | %s_val:reg32_t<=\$0x%Lx:reg32_t",$n,$const_bounds[$i+1]);
    }
    for (my $i=0; $i < scalar(@const_vals); $i++) {
	$s1 .= sprintf(" | %s_val==0x%Lx:reg32_t", $n, $const_vals[$i]);
	$s2 .= sprintf(" | %s_val==0x%Lx:reg32_t", $n, $const_vals[$i]);
    }
    push @const_bounds_ec, ("-extra-condition", $s1);
    push @const_bounds_ec, ("-extra-condition", $s2);
}

#print "const_bounds_ec = @const_bounds_ec\n";

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt,$ret_adapt) = (@_);
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
    my @args = ($fuzzball, "-linux-syscalls", "-arch", $arch_str,
		"-load-base", "0x8000",
		$bin,
		@solver_opts, "-fuzz-start-addr", $fuzz_start_addr,
		"-symbolic-word", "$arg_addr[0]=a",
		"-symbolic-word", "$arg_addr[1]=b",
		"-symbolic-word", "$arg_addr[2]=c",
		"-symbolic-word", "$arg_addr[3]=d",
		"-symbolic-word", "$arg_addr[4]=e",
		"-symbolic-word", "$arg_addr[5]=f",
		"-symbolic-word", "$arg_addr[6]=g",
		"-symbolic-word", "$arg_addr[7]=h",
		"-symbolic-word", "$arg_addr[8]=i",
		"-symbolic-word", "$arg_addr[9]=j",
		"-symbolic-word", "$arg_addr[10]=k",
		"-symbolic-word", "$arg_addr[11]=l",
		"-symbolic-word", "$arg_addr[12]=m",
		"-dont-compare-memory-sideeffects",
		"-trace-sym-addr-details",
		"-trace-sym-addrs",
		"-trace-syscalls",
		"-omit-pf-af",
		"-trace-temps",
		"-trace-regions",
		"-trace-memory-snapshots",
		"-trace-tables",
		"-table-limit","12",
		#"-save-decision-tree-interval", 1,
		#"-trace-decision-tree",
		"-trace-binary-paths-bracketed",
#"-narrow-bitwidth-cutoff","1",
		"-trace-basic",
		# "-trace-eip",
		# "-trace-registers",
		#"-trace-stmts",
		# "-trace-ir",
		# "-trace-insns",
		# "-trace-loads",
		# "-trace-eval",
		# "-trace-stores",
		# "-trace-offset-limit",
		"-trace-conditions",
		"-trace-decisions",
		# "-tracepoint","0x27dac:R2:reg32_t",
		#"-trace-solver",
		#"-save-solver-files", 
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		@synth_opt, @conc_adapt, @const_bounds_ec,
		@synth_ret_opt, @conc_ret_adapt,
		"-return-zero-missing-x64-syscalls",
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-region-limit", $region_limit,
		"-branch-preference", "$match_jne_addr:1",
		"-redirect-stderr-to-stdout",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-trace-stopping",
		"-random-seed", int(rand(10000000)),
		"-fragments",
		"--", $bin, $f1num, $f2num, "g", $frag_file_name);
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
    my(@region_contents);
    $this_ce = 0;
    my $f1_completed = 0;
    $f1_completed_count = 0;
    $iteration_count = 0;
    my $stp_timeout = 0;
    my $fatal_error = 0;
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
	    for my $i (1 .. $region_limit+1) { push @tmp_reg_arr, 0; }
	    for my $i (1 .. ($f1nargs+1)) { push @region_contents, [@tmp_reg_arr]; }
	    $iteration_count++;
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
		if ($v =~ /^([a-m])=(0x[0-9a-f]+)$/) {
		    my $index = ord($1) - ord("a");
		    $ce[$index] = hex $2;
		    if ($arg_to_regnum[$index] != 0) {
			$ce[$index] = $sane_addr;
			$regnum_to_saneaddr[$arg_to_regnum[$index]] = $sane_addr;
			$sane_addr = $sane_addr + $region_limit;
		    }
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
	} elsif (/Address [a-m]_([0-9])+:reg32_t is region ([0-9]+)/ and $f1_completed == 0 ) {
	    my $add_line = $_;
	    my $add_var = -1;
	    for my $v (split(/ /, $add_line)) {
		if ($v =~ /^[a-m]_([0-9]+):reg32_t$/) { # matches argument name
		    $add_var = ord($v) - ord('a');
		} elsif ($v =~ /^[0-9]$/) { # matches region number
		    if ($add_var < $f1nargs and $add_var >= 0) {
			$arg_to_regnum[$add_var] = int($v);
			$regnum_to_arg[int($v)]=$add_var;
			# 1 indicates symbolic input created a region
			$region_contents[$v][0]=1;
			print "Found region $v";
		    }
		}
	    }
	} elsif (/.*STP timeout.*/ and ($f1_completed == 1)) {
	    $stp_timeout = 1;
	} elsif (/.*Fatal error.*/) {
	    $fatal_error = 1;
	}
	print "  $_";
    }
    close LOG;
    if ($matches == 0 and $fails == 0) {
	die "Missing results from check run";
    }
    if ($fails == 0) {
	return (1, [], [], $stp_timeout, $fatal_error);
    } else {
	return (0, [@ce], [@fuzzball_extra_args], $stp_timeout, $fatal_error);
    }
}

# Given a set of tests, run with the adaptor symbolic to see if we can
# synthesize an adaptor that works for those tests.
sub try_synth {
    my($testsr, $_fuzzball_extra_args) = @_;
    my @fuzzball_extra_args = @{ $_fuzzball_extra_args };
    foreach my $i (0 .. $#fuzzball_extra_args) {
	print "fuzzball_extra_args: fuzzball_extra_args[$i]= $fuzzball_extra_args[$i]\n";
    }
    open(TESTS, ">tests");
    for my $t (@$testsr) {
	my @vals = (@$t, (0) x 13);
	splice(@vals, 13);
	my $test_str = join(" ", map(sprintf("0x%x", $_), @vals));
	print TESTS $test_str, "\n";
    }
    close TESTS;
    my @args = ($fuzzball, "-linux-syscalls", "-arch", $arch_str, $bin,
		"-load-base", "0x8000",
		"-dont-compare-memory-sideeffects",
		@solver_opts, 
		"-fuzz-start-addr", $fuzz_start_addr,
		"-trace-temps",
		#tell FuzzBALL to run in adaptor search mode, FuzzBALL will run in
		#counter example search mode otherwise
		"-adaptor-search-mode",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-table-limit","12",
		"-return-zero-missing-x64-syscalls",
		@synth_opt, @const_bounds_ec,
		@synth_ret_opt,
		"-match-syscalls-in-addr-range",
		$f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
		"-branch-preference", "$match_jne_addr:0",
		"-redirect-stderr-to-stdout",
		"-trace-conditions", "-omit-pf-af",
		"-trace-syscalls",
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
		# "-trace-eip",
		# "-trace-registers",
		#"-trace-stmts",
		# "-trace-insns",
		#"-trace-loads",
		#"-trace-stores",
		#"-trace-solver",
		#"-save-solver-files", 
		"-zero-memory",
		@fuzzball_extra_args,
		"-region-limit", $region_limit,
		"-random-seed", int(rand(10000000)),
		"-fragments",
		"--", $bin, $f1num, $f2num, "f", "tests", $frag_file_name);
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
		#print "Found 1 and 2 = $1 and $2\n";
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
    for my $fr (@fields) {
	push @afields, $fields{$fr->[0]};
	#print "try_synth: pushing $fr->[0] = $fields{$fr->[0]}\n";
    }
    for my $fr (@ret_fields) {
	push @bfields, $fields{$fr->[0]};
	#print "try_synth: pushing $fr->[0] = $fields{$fr->[0]}\n";
    }
    return ([@afields],[@bfields]);
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

# Set these to test a specific adaptor
$adapt->[0]=1;
$adapt->[1]=0;
# $adapt->[2]=1;
# $adapt->[3]=0;
# $adapt->[4]=1;
# $adapt->[5]=255;

print "default adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
my @tests = ();
my $done = 0;
my $start_time = time();
my $reset_time = time();
my $total_ce_time = 0;
my $total_as_time = 0;
my $diff;
my $diff1;

sub get_adaptor_str {
    my $a = shift(@_);
    my $a_str = "{";
    for(my $i=0; $i < $#$a; $i+=2) {
	$a_str .= sprintf("(%d, %d)", $a->[$i], $a->[$i+1]);
	if($i + 2 < $#$a) { $a_str .= ", "; }
    }
    $a_str = $a_str . "}";
    return $a_str;
}

while (!$done) {
    my $adapt_s = get_adaptor_str($adapt);
    my $ret_adapt_s = get_adaptor_str($ret_adapt); #join(",", @$ret_adapt);
    print "Checking $adapt_s and $ret_adapt_s:\n";
    my($res, $cer, $_fuzzball_extra_args, $stp_timeout, $fatal_error) = check_adaptor($adapt,$ret_adapt);
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last CE search time = $diff1\n";
    $total_ce_time += $diff1;
    $reset_time = time();
    if ($res) {
	print "Success!\n";
	print "Final test set:\n";
	for my $tr (@tests) {
	    print " $tr->[0], $tr->[1], $tr->[2], $tr->[3], $tr->[4], $tr->[5], $tr->[6], $tr->[7], $tr->[8], $tr->[9], $tr->[10], $tr->[11], $tr->[12]\n";
	}
	my $verified="partial";
	if ($f1_completed_count == $iteration_count) { $verified="complete"; }
	if ($stp_timeout == 1) { $verified = "timed-out"; }
	if ($fatal_error == 1) { $verified = "fatal-error"; }
	print "Final adaptor for $frag_file_name is $adapt_s and $ret_adapt_s with $f1_completed_count,$iteration_count,$verified\n";
	print "total_as_time = $total_as_time, total_ce_time = $total_ce_time\n";
	get_adaptor_str($adapt);
	$done = 1;
	last;
    } else {
	push @fuzzball_extra_args_arr, @{ $_fuzzball_extra_args };
	my $ce_s = join(", ", @$cer);
	print "Mismatch on input $ce_s; adding as test\n";
	push @tests, [@$cer];
    }

    ($adapt,$ret_adapt) = try_synth(\@tests, \@fuzzball_extra_args_arr);
    print "Synthesized arg adaptor ".get_adaptor_str($adapt).
	" and return adaptor ".get_adaptor_str($ret_adapt)."\n";
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last AS search time = $diff1\n";
    $total_as_time += $diff1;
    $reset_time = time();
}
