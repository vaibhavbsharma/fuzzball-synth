#!/usr/bin/perl

use strict;

my $bin = "./two-funcs";
die "Usage: synth-one.pl <f1num> <f2num> <seed> <default adaptor(0=zero,1=identity) [<lower bound for constant> <upper bound for constant>] <recompile $bin=1, use $bin as-is=0> <verbose=1, non-verbose=0, extra-verbose=2 (is logging-heavy, be warned)>"
  unless @ARGV == 8;
my($f1num, $f2num, $rand_seed, $default_adaptor_pref, $const_lb, $const_ub, $recompile, $verbose) = @ARGV;

srand($rand_seed);
my $path_depth_limit = 300;
my $iteration_limit = 4000;

my $region_limit = 936;

my $sane_addr = 0x42420000; # starting sane address also assumed in SRFM#region_for (SRFM.ml line 873)

my @fuzzball_extra_args_arr;
my $numTests=0;
my $fuzzball="fuzzball";
my $stp="stp";

my $f1_completed_count = 0;
my $iteration_count = 0;
my $adaptor_score = 0;

if ($recompile == 1) {
    print "compiling binary: ";
    my $unused = `gcc -static -DF2VER=0 -DF2NARGS=3 two-funcs.c -g -o two-funcs -lpthread`;
    my $gcc_ec = $?;
    die "failed to compile $bin" unless $gcc_ec == 0;
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
print "fuzz-start-addr: $fuzz_start_addr\n";
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
  (["a_type",  "reg8_t", "%01x"],
   ["a_val",      "reg64_t", "%016x"],
   ["b_type",  "reg8_t", "%01x"],
   ["b_val",      "reg64_t", "%016x"],
   ["c_type",  "reg8_t", "%01x"],
   ["c_val",      "reg64_t", "%016x"],
   ["d_type",  "reg8_t", "%01x"],
   ["d_val",      "reg64_t", "%016x"],
   ["e_type",  "reg8_t", "%01x"],
   ["e_val",      "reg64_t", "%016x"],
   ["f_type",  "reg8_t", "%01x"],
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
my @verbose_1_opts = (
    "-trace-conditions",
    "-trace-decisions",
    "-trace-adaptor",
    "-trace-sym-addr-details",
    "-trace-sym-addrs",
    "-trace-syscalls",
    "-trace-temps",
    "-trace-memory-snapshots",
    "-trace-tables",
    "-trace-binary-paths-bracketed",
    "-trace-solver",
    "-trace-regions");

my @verbose_2_opts = (@verbose_1_opts,
		      "-trace-offset-limit",
		      "-trace-basic",
		      "-trace-eip",
		      "-trace-registers",
		      "-trace-stmts",
		      "-trace-insns",
		      "-trace-loads",
		      "-trace-stores");
my @verbose_opts = ($verbose == 1) ? @verbose_1_opts : (($verbose == 2) ? @verbose_2_opts : ());

my @common_opts = (
    "-no-fail-on-huer",
    "-return-zero-missing-x64-syscalls",
    "-region-limit", $region_limit,
    "-trace-iterations", "-trace-assigns", "-solve-final-pc",
    "-trace-stopping",
    "-table-limit","12",
    "-omit-pf-af",
    "-match-syscalls-in-addr-range",
    $f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call,
    "-random-seed", int(rand(10000000)),
    "-nonzero-divisors");

my @solver_opts = ("-solver", "smtlib-batch", 
		   "-save-solver-files",
		   "-solver-path", $stp, "-solver-timeout",5,"-timeout-as-unsat");

my @synth_opt = ("-synthesize-adaptor",
		 join(":", "typeconv", $f2_call_addr, $f1nargs, $f2_addr, $f2nargs));

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
	    $s1 = sprintf("%s_type:reg8_t==0:reg8_t | %s_val:reg64_t>=\$0x%Lx:reg64_t",$n,$n,$const_lb);
	    $s2 = sprintf("%s_type:reg8_t==0:reg8_t | %s_val:reg64_t<=\$0x%Lx:reg64_t",$n,$n,$const_ub);
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

# http://stackoverflow.com/questions/17860976/how-do-i-output-a-string-of-hex-values-into-a-binary-file-in-perl
sub generate_new_file
{
    my $fname = shift(@_);
    my $aref = shift(@_);

    open(BIN, ">", $fname) or die;
    binmode(BIN);

    for (my $i = 0; $i < @$aref; $i += 2)
    {
	my ($hi, $lo) = @$aref[$i, $i+1];
	print BIN pack "H*", $hi.$lo;
    }
    close(BIN);
}
# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt,$ret_adapt) = (@_);
    #print "checking arg-adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
    my @conc_adapt = ();
    if ($f2nargs > 0) {
	for my $i (0 .. $#$adapt) {
	    my($name, $ty, $fmt) = @{$fields[$i]};
	    my $val = $adapt->[$i];
	    my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	    push @conc_adapt, ("-extra-condition", $s);
	}
    }
    my @conc_ret_adapt = ();
    for my $i (0 .. $#$ret_adapt) {
	my($name, $ty, $fmt) = @{$ret_fields[$i]};
	my $val = $ret_adapt->[$i];
	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	push @conc_ret_adapt, ("-extra-condition", $s);
    }
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64",
		$bin,
		@solver_opts, "-fuzz-start-addr", $fuzz_start_addr,
		"-symbolic-long", "$arg_addr[0]=a",
		"-symbolic-long", "$arg_addr[1]=b",
		"-symbolic-long", "$arg_addr[2]=c",
		"-symbolic-long", "$arg_addr[3]=d",
		"-symbolic-long", "$arg_addr[4]=e",
		"-symbolic-long", "$arg_addr[5]=f",
		"-trace-regions",  # do not turn off, necessary for finding the "Address <> is region <>" line in output below
		@verbose_opts,
		#"-narrow-bitwidth-cutoff","1", # I have no idea what this option does
		@synth_opt, @conc_adapt, @const_bounds_ec,
		@synth_ret_opt, @conc_ret_adapt,
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-branch-preference", "$match_jne_addr:0",
		@common_opts,
		"--", $bin, $f1num, $f2num, "g");
    my @printable;
    for my $a (@args) {
	if ($a =~ /[\s|<>]/) {
	    push @printable, "'$a'";
	} else {
	    push @printable, $a;
	}
    }
    if ($verbose != 0) { print "@printable\n"; }
    open(LOG, "-|", @args);
    my($matches, $fails) = (0, 0);
    my(@ce, $this_ce);
    my(@arg_to_regnum, @regnum_to_arg, @fuzzball_extra_args, @regnum_to_saneaddr);
    my(@region_contents);
    $this_ce = 0;
    my $f1_completed = 0;
    $f1_completed_count = 0;
    $iteration_count = 0;
    while (<LOG>) {
	if ($_ eq "Match\n" ) {
	    $matches++;
	} elsif (/^Iteration (.*):$/) {
	    $f1_completed = 0;
	    @arg_to_regnum = (0) x $f1nargs;
	    @regnum_to_arg = (0) x 1000;
	    @regnum_to_saneaddr = (0) x ($f1nargs+1);
	    my @tmp_reg_arr;
	    @region_contents = ();
	    # region_contents is row-indexed by argument number starting from 0
	    # but col-indexed from 1 up to region_limit
	    # this is because region_contents[i][0] indicates if a argument
	    # has a region assigned to it
	    for my $i (1 .. $region_limit+1) { push @tmp_reg_arr, 0; }
	    for my $i (0 .. $f1nargs-1) { push @region_contents, [@tmp_reg_arr]; }
	    for my $i (0 .. $#region_contents) {
		for my $j (0 .. $#{$region_contents[$i]}) {
		    $region_contents[$i][$j]=0;
		}
	    }
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
		if ($v =~ /^([a-f])=(0x[0-9a-f]+)$/) {
		    my $index = ord($1) - ord("a");
		    $ce[$index] = hex $2;
		    # printf("arg_to_regnum[$index] = %d\n",
		    # 	   $arg_to_regnum[$index]);
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
		    # $1 -> region number, starts with 1
		    # $2 -> offset within region, starts with 0
		    # $3 -> value to be set, any value
		    my $region_number = $1 + 0;
		    my $region_offset = hex $2;
		    $region_offset += 1; # because first value is 1 if region is used
		    my $arg_num = $regnum_to_arg[$region_number];
		    # printf("arg_num = %d, region_number = $region_number\n", $arg_num);
		    if($regnum_to_saneaddr[$region_number] != 0) {
			$region_contents[$arg_num][$region_offset]=$3;
			# printf("region_contents[$arg_num][$region_offset] = %s (%s), with saneaddr = 0x%x\n", 
			#        $region_contents[$arg_num][$region_offset], $3,
			#        $regnum_to_saneaddr[$1]);
		    }
		    else { # printf("cannot find regnum_to_saneaddr for $1\n"); 
		    }
		}
	    }
	    for my $i (0 .. $f1nargs-1) {
		my $str_arg_contents="";
		for my $j (1 .. $region_limit) {
		    # printf("region_contents[$i][$j] = %s, sane_addr = 0x%x\n", 
		    # 	   $region_contents[$i][$j],
		    # 	   $regnum_to_saneaddr[$arg_to_regnum[$i]]);
		    my $byte="0x00";
		    if($region_contents[$i][0] == 1) {
			push @fuzzball_extra_args, "-store-byte";
			push @fuzzball_extra_args, 
			sprintf("0x%x=%s", 
				$regnum_to_saneaddr[$arg_to_regnum[$i]]+$j-1, 
				$region_contents[$i][$j]);
			# printf("pushed 0x%x=%s\n", 
			# 	$regnum_to_saneaddr[$arg_to_regnum[$i]]+$j-1, 
			# 	$region_contents[$i][$j]); 
			$str_arg_contents .= substr $region_contents[$i][$j], 2;
		    } else { 
			$str_arg_contents .= "00";
		    }
		}
		# printf("str_arg_contents = $str_arg_contents\n");;
		my @data_ary = split //, $str_arg_contents;
		generate_new_file("str_arg${i}_$numTests", \@data_ary);
	    }
	    $this_ce = 0;
	    if ($verbose != 0) { print "  $_"; }
	    last;
	} elsif (/Address [a-f]:reg64_t is region ([0-9]+)/) {
	    my $add_line = $_;
	    my $add_var = -1;
	    for my $v (split(/ /, $add_line)) {
		if ($v =~ /^[a-f]:reg64_t$/) { # matches argument name
		    $add_var = ord($v) - ord('a');
		    if($verbose != 0) { printf("add_var = $add_var\n"); }
		} elsif ($v =~ /^[0-9]$/) { # matches region number
		    if ($add_var < $f1nargs and $add_var >= 0) {
			$arg_to_regnum[$add_var] = $v-'0';
			# printf("arg_to_regnum[$add_var] = %d\n", 
			#        $arg_to_regnum[$add_var]);
			$regnum_to_arg[$v-'0'] = $add_var;
			# 1 indicates symbolic input created a region
			$region_contents[$add_var][0]=1;
		    }
		}
	    }
	} # elsif print strings used by eg/libc/exp-scripts/run-funcs.pl 
	elsif(/.*total query time = (.*)$/ || 
		/.*Query time = (.*) sec$/ || 
		/.*Starting new query.*$/) {
	    print "  $_";
	}
	if ($verbose != 0) { print "  $_"; }
    }
    close LOG;
    if ($matches == 0 and $fails == 0) {
	print "CounterExample search failed";
	die "Missing results from check run";
    }
    $numTests++;
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
    my @fuzzball_extra_args = @{ $_fuzzball_extra_args };
    if ($verbose != 0) {
	foreach my $i (0 .. $#fuzzball_extra_args) {
	    print "fuzzball_extra_args: fuzzball_extra_args[$i]= $fuzzball_extra_args[$i]\n";
	}
    }
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
		#tell FuzzBALL to run in adaptor search mode, FuzzBALL will run in
		#counter example search mode otherwise
		"-adaptor-search-mode",
		@verbose_opts,
		@synth_opt, @const_bounds_ec,
		@synth_ret_opt,
		"-branch-preference", "$match_jne_addr:1",
		"-zero-memory",
		@fuzzball_extra_args,
		@common_opts,
		"--", $bin, $f1num, $f2num, "f", "tests");
    my @printable;
    for my $a (@args) {
	if ($a =~ /[\s|<>]/) {
	    push @printable, "'$a'";
	} else {
	    push @printable, $a;
	}
    }
    if ($verbose != 0) { print "@printable\n"; }
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
	    if ($verbose != 0) { print "  $_"; }
	    last;
	} elsif (/^adaptor_score = (.*)$/ and $success) {
	    $adaptor_score = $1;
	} # elsif print strings used by eg/libc/exp-scripts/run-funcs.pl 
	elsif(/.*total query time = (.*)$/ || 
		/.*Query time = (.*) sec$/ || 
		/.*Starting new query.*$/) {
	    print "  $_";
	}

	if ($verbose != 0) { print "  $_" unless /^Input vars:/; }
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
	if ($i%2 == 0) { # X_type field
	    $adapt->[$i] = 1;
	    $adapt->[$i+1] = 1;
	}
    }
}

# Set these to test a specific adaptor
$adapt->[0]=1;
#  $adapt->[1]=0;
#  $adapt->[2]=1;
#  $adapt->[3]=0;
#  $adapt->[4]=1;
#  $adapt->[5]=10;

print "default adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
my @tests = ();
my $done = 0;
my $start_time = time();
my $reset_time = time();
my $total_ce_time = 0;
my $total_as_time = 0;
my $diff;
my $diff1;
`rm str_arg*`;
`rm fuzzball-tmp-*`;
while (!$done) {
    my $adapt_s = join(",", @$adapt);
    my $ret_adapt_s = join(",", @$ret_adapt);
    print "Checking $adapt_s and $ret_adapt_s:\n";
    my($res, $cer, $_fuzzball_extra_args) = check_adaptor($adapt,$ret_adapt);
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last CE search time = $diff1\n";
    $total_ce_time += $diff1;
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
	my $scaled_adaptor_score = ($adaptor_score * $f1_completed_count) / $iteration_count;
	print "Final adaptor is $adapt_s and $ret_adapt_s with $f1_completed_count,$iteration_count,$verified, adaptor_score = $scaled_adaptor_score ($adaptor_score)\n";
	print "total_as_time = $total_as_time, total_ce_time = $total_ce_time\n";
	$done = 1;
	last;
    } else {
	push @fuzzball_extra_args_arr, @{ $_fuzzball_extra_args };
	my $ce_s = join(", ", @$cer);
	print "Mismatch on input $ce_s; adding as test\n";
	push @tests, [@$cer];
    }

    ($adapt,$ret_adapt) = try_synth(\@tests, \@fuzzball_extra_args_arr);
    print "Synthesized arg adaptor ".join(",",@$adapt).
	" and return adaptor ".join(",",@$ret_adapt)."\n";
    $diff = time() - $start_time;
    $diff1 = time() - $reset_time;
    print "elapsed time = $diff, last AS search time = $diff1\n";
    $total_as_time += $diff1;
    $reset_time = time();
}
