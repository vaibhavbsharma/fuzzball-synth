#!/usr/bin/perl

use strict;

# Only script argument is a random seed, to see new behavior
srand($ARGV[0]);

# Paths to binaries: these probably differ on your system. You can add
# your locations to the list, or set the environment variable.
my $smcc_umn = "/home/fac05/mccamant/bitblaze/fuzzball/trunk-gh";
my $smcc_home = "/home/smcc/bitblaze/fuzzball/trunk-gh";
my $fuzzball;
if (exists $ENV{FUZZBALL_LOC}) {
    $fuzzball = $ENV{FUZZBALL_LOC};
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
} elsif (-x "$smcc_umn/stp/stp") {
    $stp = "$smcc_umn/stp/stp";
} elsif (-x "$smcc_home/stp/stp") {
    $stp = "$smcc_home/stp/stp";
} else {
    $stp = "stp";
}

my $bin = "./low-bit";

# Try to figure out the code and data addresses we need based on
# matching the output of "nm" and "objdump". Not the most robust
# possible approach.

my $main_addr = "0x" . substr(`nm $bin | fgrep " T main"`, 0, 16);

my($atoi_x_addr, $atoi_y_addr) =
  map("0x" . substr($_, 2, 6), `objdump -dr $bin | grep 'call.*strtoul'`);

my $fields_addr = "0x" . substr(`nm $bin | fgrep " B the_adaptor"`, 0, 16);

my $match_jne_addr =
  "0x" . substr(`objdump -dr $bin | grep 'jne.*compare+'`, 2, 6);

# An adaptor is represented by a C struct, whose structure we
# reproduce here.
# Field [0]: offset within struct
# Field [1]: field name
# Field [2]: size in bytes (must be 1, 2, 4, or 8)
# Field [3]: printf format for the string form
# Field [4]: validity condition

my @fields =
  ([ 0, "a_is_const", 4, "%01x",
        'a_is_const:reg32_t <= 1:reg32_t'],
   [ 4, "a_val",      4, "%08x",
        'a_is_const:reg32_t == 1:reg32_t | a_val:reg32_t <= 1:reg32_t'],
   [ 8, "b_is_const", 4, "%01x",
        'b_is_const:reg32_t <= 1:reg32_t'],
   [12, "b_val",      4, "%08x",
        'b_is_const:reg32_t == 1:reg32_t | b_val:reg32_t <= 1:reg32_t'],
   [16, "c_is_const", 4, "%01x",
        'c_is_const:reg32_t <= 1:reg32_t'],
   [20, "c_val",      4, "%08x",
        'c_is_const:reg32_t == 1:reg32_t | c_val:reg32_t <= 1:reg32_t'],
   [24, "d_is_const", 4, "%01x",
        'd_is_const:reg32_t <= 1:reg32_t'],
   [28, "d_val",      4, "%08x",
        'd_is_const:reg32_t == 1:reg32_t | d_val:reg32_t <= 1:reg32_t'],
);

my @solver_opts = ("-solver", "smtlib", "-solver-path", $stp);

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

# Given the specification of an adaptor, execute it with symbolic
# inputs to either check it, or produce a counterexample.
sub check_adaptor {
    my($adapt) = @_;
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64",
		$bin, "-env", "ADAPTOR=$adapt",
		@solver_opts, "-fuzz-start-addr", $main_addr,
		"-skip-call-ret-symbol-once", "$atoi_x_addr=x",
		"-skip-call-ret-symbol-once", "$atoi_y_addr=y",
		"-branch-preference", "$match_jne_addr:0",
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-random-seed", int(rand(10000000)),
		"--", $bin, "0", "0");
    open(LOG, "-|", @args);
    my($matches, $fails) = (0, 0);
    my(@ce, $this_ce);
    $this_ce = 0;
    while (<LOG>) {
	if ($_ eq "Match\n") {
	    $matches++;
	} elsif ($_ eq "Mismatch\n") {
	    $fails++;
	    $this_ce = 1;
	} elsif (/^Input vars: (.*)$/ and $this_ce) {
	    my $vars = $1;
	    @ce = (0, 0);
	    for my $v (split(/ /, $vars)) {
		if ($v =~ /^x=(0x[0-9a-f]+)$/) {
		    $ce[0] = hex $1;
		} elsif ($v =~ /^y=(0x[0-9a-f]+)$/) {
		    $ce[1] = hex $1;
		}
	    }
	    $this_ce = 0;
	    print "  $_";
	    last;
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
	return (0, [@ce]);
    }
}

# Given a set of tests, run with the adaptor symbolic to see if we can
# synthesize an adaptor that works for those tests.
sub try_synth {
    my($testsr) = @_;
    open(TESTS, ">tests");
    for my $t (@$testsr) {
	printf TESTS "%x %x\n", $t->[0], $t->[1];
    }
    close TESTS;
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64", $bin,
		@solver_opts, "-fuzz-start-addr", $main_addr,
		@sym_field_opts,
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-branch-preference", "$match_jne_addr:1",
		#"-trace-conditions", "-trace-temps", "-omit-pf-af",
		"-random-seed", int(rand(10000000)),
		"--", $bin, "tests");
    open(LOG, "-|", @args);
    my($success, %fields);
    $success = 0;
    while (<LOG>) {
	if ($_ eq "All tests succeeded!\n") {
	    $success = 1;
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
    for my $fr (@fields) {
	push @afields, sprintf($fr->[3], $fields{$fr->[1]});
    }
    return join(",", @afields);
}


# Main loop: starting with a stupid adaptor and no tests, alternate
# between test generation and synthesis.
my $adapt = "0,00000000,0,00000000,0,00000000,0,00000000";
my @tests = ();
my $done = 0;
while (!$done) {
    print "Checking $adapt:\n";
    my($res, $cer) = check_adaptor($adapt);
    if ($res) {
	print "Success!\n";
	print "Final test set:\n";
	for my $tr (@tests) {
	    print " $tr->[0], $tr->[1]\n";
	}
	print "Final adaptor is $adapt\n";
	$done = 1;
	last;
    } else {
	my($x, $y) = @$cer;
	print "Mismatch on input $x, $y; adding as test\n";
	push @tests, [$x, $y];
    }

    $adapt = try_synth(\@tests);
    print "Synthesized adaptor $adapt\n";
}
