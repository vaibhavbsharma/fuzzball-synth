#!/usr/bin/perl

use strict;


die "Usage: synth-one.pl <f1num> <f2num> <seed> <default adaptor(0=zero,1=identity)"
  unless @ARGV == 4;
my($f1num, $f2num, $rand_seed, $default_adaptor_pref) = @ARGV;

srand($rand_seed);
my $path_depth_limit = 300;
my $iteration_limit = 4000;

my $region_limit = 2;

my $sane_addr = 0x42420000;

my @fuzzball_extra_args_arr;

# Paths to binaries: these probably differ on your system. You can add
# your locations to the list, or set the environment variable.
my $smcc_umn = "/home/fac05/mccamant/bitblaze/fuzzball/trunk-gh";
my $smcc_home = "/home/smcc/bitblaze/fuzzball/trunk-gh";
my $git_fuzzball = "../../../../../tools/fuzzball";
my $fuzzball;
if (exists $ENV{FUZZBALL_LOC}) {
    $fuzzball = $ENV{FUZZBALL_LOC};
} elsif (-x "$git_fuzzball/exec_utils/fuzzball") {
    $fuzzball = "$git_fuzzball/exec_utils/fuzzball";
} elsif (-x "$smcc_umn/exec_utils/fuzzball") {
    $fuzzball = "$smcc_umn/exec_utils/fuzzball";
} elsif (-x "$smcc_home/exec_utils/fuzzball") {
    $fuzzball = "$smcc_home/exec_utils/fuzzball";
} else {
    $fuzzball = "fuzzball";
}

my $stp;
if (exists $ENV{STP_LOC}) {
    $stp = $ENV{STP_LOC};
} elsif (-x "$git_fuzzball/stp/stp") {
    $stp = "$git_fuzzball/stp/stp";
} elsif (-x "$smcc_umn/stp/stp") {
    $stp = "$smcc_umn/stp/stp";
} elsif (-x "$smcc_home/stp/stp") {
    $stp = "$smcc_home/stp/stp";
} else {
    $stp = "stp";
}

my $f1_completed_count = 0;
my $iteration_count = 0;

my $bin = "./struct_adaptor";

#  my @func_info;
#  open(F, "<types-no-float-1204.lst") or die;
#  while (<F>) {
#      my($num, $nargs, $name, $type) = split(" ", $_, 4);
#      if ($nargs =~ /\+/) {
#  	$nargs = substr($nargs,0,1);
#      }
#      push @func_info, [$num, $nargs, $name, $type];
#  }
#  close F;

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

my $match_syscalls_range = ("-match-syscalls-in-addr-range",
			    $f1_call_addr.":".$post_f1_call.":".$f2_call_addr.":".$post_f2_call);
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
#    print "f1:   $f1_addr @ $f1_call_addr\n";
#    print "f2:   $f2_addr\n";
#    print "wrap_f2: $wrap_f2_addr @ $f2_call_addr\n";
for my $i (0 .. 5) {
    print "arg$i: $arg_addr[$i]\n";
}
print "branch: $match_jne_addr\n";
#  printf "%d = %s(%d)\n", $f1num, $func_info[$f1num][2], $func_info[$f1num][1];
#  printf "%d = %s(%d)\n", $f2num, $func_info[$f2num][2], $func_info[$f2num][1];

# Field [0]: field offset
# Field [1]: field name
# Field [2]: field size
# Field [3]: printf format for the string form
# Field [4]: bound on field as -extra-condition
# Field [5]: Vine type
 
my @fields =
  (
   [0, "field1", 4, "%08x", 'field1:reg32_t <= 1:reg32_t', 'reg32_t'],
   [4, "field2", 4, "%08x", 'field2:reg32_t <= 1:reg32_t', 'reg32_t'],
  );
#    my @ret_fields = 
#    (
#       ["ret_type",  "reg8_t", "%01x"],
#       ["ret_val",   "reg64_t", "%016x"],
#    );

my $fields_addr = "0x" . substr(`nm $bin | fgrep " B the_adaptor"`, 0, 16);

my @sym_field_opts;
for my $fr (@fields) {
    my $addr = sprintf("0x%08x", hex($fields_addr) + $fr->[0]);
    my $name = $fr->[1];
    my $size = {1 => "byte", 2 => "short",
		4 => "word", 8 => "long"}->{$fr->[2]};
    push @sym_field_opts, "-symbolic-$size", "$addr=$name";
    if (@$fr > 4) {
	push @sym_field_opts, "-extra-condition", $fr->[4];
    }
}
#print join(" ", @sym_field_opts), "\n";

my($f1nargs, $f2nargs) = (1, 1);
#my($f1nargs, $f2nargs) = ($func_info[$f1num][1], $func_info[$f2num][1]);
#$f1nargs=6;
#$f2nargs=6;

my @solver_opts = ("-solver", "smtlib-batch", "-solver-path", $stp, "-solver-timeout",5,"-timeout-as-unsat");

# my @synth_ret_opt = ("-synthesize-return-adaptor",
# 		 join(":", "return-typeconv", $f2_addr, $post_f2_call, $f2nargs));
# print "synth_ret_opt = @synth_ret_opt\n";

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt) = (@_);
    #    my($adapt,$ret_adapt) = (@_);
    #print "checking arg-adaptor = @$adapt ret-adaptor = @$ret_adapt\n";
    my @conc_adapt = ();
    for my $i (0 .. $#$adapt) {
	my($offset, $name, $size, $fmt, $ec, $ty) = @{$fields[$i]};
	my $val = $adapt->[$i];
	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
	push @conc_adapt, ("-extra-condition", $s);
    }
    #    my @conc_ret_adapt = ();
    #    for my $i (0 .. $#$ret_adapt) {
    #    	my($name, $ty, $fmt) = @{$ret_fields[$i]};
    #    	my $val = $ret_adapt->[$i];
    #    	my $s = sprintf("%s:%s==0x$fmt:%s", $name, $ty, $val, $ty);
    #    	push @conc_ret_adapt, ("-extra-condition", $s);
    #    }
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
		#"-save-solver-files", 
		#@match_syscalls_range,
		@sym_field_opts, @conc_adapt,
		#@synth_ret_opt, @conc_ret_adapt,
		"-return-zero-missing-x64-syscalls",
		#"-path-depth-limit", $path_depth_limit,
		"-iteration-limit", $iteration_limit,
		"-region-limit", $region_limit,
		"-branch-preference", "$match_jne_addr:0",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-trace-stopping",
		"-random-seed", int(rand(10000000)),
		"--", $bin, $f1num, $f2num, "g");
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
    my(@ce, $this_ce, @arg_to_regnum, @regnum_to_arg, @fuzzball_extra_args, @regnum_to_saneaddr);
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
	    @regnum_to_arg = (0) x $f1nargs;
	    @regnum_to_saneaddr = (0) x 256;
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
		    if ($arg_to_regnum[$index] != 0) {
			$ce[$index] = $sane_addr;
			$regnum_to_saneaddr[$arg_to_regnum[$index]] = $sane_addr;
			$sane_addr = $sane_addr + $region_limit;
		    }
		} 
	    }
	    for my $v (split (/ /, $vars)) {
		if($v =~ /^region_([0-9]+)_byte_0x([0-9]+)=(0x[0-9a-f]+)$/) {
		    print "region assignment $1 $2 $3 for arg $regnum_to_arg[$1]\n";
		    # push @fuzzball_extra_args, "-store-byte $regnum_to_saneaddr[$1]=$3";
		    push @fuzzball_extra_args, "-store-byte";
		    push @fuzzball_extra_args, sprintf("0x%x=%s",$regnum_to_saneaddr[$1]+$2,$3);
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
		} elsif ($v =~ /^[0-9]$/) { # matches region number
		    if ($add_var < $f1nargs and $add_var >= 0) {
			$arg_to_regnum[$add_var] = $v-'0';
			$regnum_to_arg[$v-'0']=$add_var;
		    }
		}
	    }
	} 
	print "  $_";
    }
    close LOG;
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
    my @fuzzball_extra_args = @{ $_fuzzball_extra_args };
    foreach my $i (0 .. $#fuzzball_extra_args) {
	print "fuzzball_extra_args: fuzzball_extra_args[$i]= $fuzzball_extra_args[$i]\n";
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
		"-trace-temps",
		#tell FuzzBALL to run in adaptor search mode, FuzzBALL will run in
		#counter example search mode otherwise
		"-adaptor-search-mode",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-table-limit","12",
		"-return-zero-missing-x64-syscalls",
		@sym_field_opts,
		#@synth_ret_opt,
		#@match_syscalls_range,
		"-branch-preference", "$match_jne_addr:1",
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
		#"-trace-eip",
		#"-trace-registers",
		#"-trace-stmts",
		#"-trace-insns",
		#"-trace-loads",
		#"-trace-stores",
		#"-trace-solver",
		#"-save-solver-files", 
		@fuzzball_extra_args,
		"-region-limit", $region_limit,
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
		$v =~ /^((\w+)([0-9]))=(0x[0-9a-f]+)$/
		  or die "Parse failure on variable assignment <$v>";
		$fields{$1} = hex $4;
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
	push @afields, sprintf($fr->[3], $fields{$fr->[1]});
    }
    #    for my $fr (@ret_fields) {
    #    	push @bfields, $fields{$fr->[0]};
    #    	#print "try_synth: pushing $fr->[0] = $fields{$fr->[0]}\n";
    #    }
    #    return ([@afields],[@bfields]);
    return ([@afields]);
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
#my $ret_adapt = [(0) x @ret_fields];

# Setting up the default adaptor to be the identity adaptor
if ($default_adaptor_pref == 1) {
    my $f1_narg_counter=0;
    for my $i (0 .. $#$adapt) {
	$adapt->[$i] = $i;
    }
}

print "default adaptor = @$adapt\n"; # ret-adaptor = @$ret_adapt\n";
my @tests = ();
my $done = 0;
while (!$done) {
    my $adapt_s = join(",", @$adapt);
    #my $ret_adapt_s = join(",", @$ret_adapt);
    print "Checking $adapt_s\n"; # and $ret_adapt_s:\n";
    my($res, $cer, $_fuzzball_extra_args) = check_adaptor($adapt); #,$ret_adapt);
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
	print "Final adaptor is $adapt_s with $f1_completed_count,$iteration_count,$verified\n";
	#print "Final adaptor is $adapt_s and $ret_adapt_s with $f1_completed_count,$iteration_count,$verified\n";
	$done = 1;
	last;
    } else {
	push @fuzzball_extra_args_arr, @{ $_fuzzball_extra_args };
	my $ce_s = join(", ", @$cer);
	print "Mismatch on input $ce_s; adding as test\n";
	push @tests, [@$cer];
    }

    $adapt = try_synth(\@tests, \@fuzzball_extra_args_arr);
    #    ($adapt,$ret_adapt) = try_synth(\@tests, \@fuzzball_extra_args_arr);
    print "Synthesized arg adaptor ".join(",",@$adapt)."\n";
	#" and return adaptor ".join(",",@$ret_adapt)."\n";
}
