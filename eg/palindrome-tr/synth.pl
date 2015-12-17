#!/usr/bin/perl

use strict;

# Only script argument is a random seed, to see new behavior
if (@ARGV >= 1) {
    srand($ARGV[0]);
}

my $max_len = 5;

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

my $bin = "./palindrome";

# Try to figure out the code and data addresses we need based on
# matching the output of "nm" and "objdump". Not the most robust
# possible approach.

my $main_addr = "0x" . substr(`nm $bin | fgrep " T main"`, 0, 16);

my $fields_addr = "0x" . substr(`nm $bin | fgrep " B the_adaptor"`, 0, 16);

my $input_addr = "0x" . substr(`nm $bin | fgrep " B the_input"`, 0, 16);

my $match_jne_addr =
  "0x" . substr(`objdump -dr $bin | grep 'jne.*compare+'`, 2, 6);

sub escape_str {
    my($s) = @_;
    $s =~ s[([^ -~])][sprintf "\\x%02x", ord($1)]eg;
    return $s;
}

# An adaptor is represented by a C struct, whose structure we
# reproduce here.
# Field [0]: offset within struct
# Field [1]: field name
# Field [2]: size in bytes (must be 1, 2, 4, or 8)
# Field [3]: printf format for the string form
my @fields;

for my $i (0 .. 255) {
    push @fields, [$i, "tableX".sprintf("%02x", $i), 1, "%02x"];
}

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
		$bin,
		@solver_opts, "-fuzz-start-addr", $main_addr,
		"-symbolic-cstring", $input_addr . "+" . $max_len,
		"-branch-preference", "$match_jne_addr:0",
		"-table-limit", 8,
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-random-seed", int(rand(10000000)),
		"--", $bin, "s", $adapt);
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
	    @ce = (0) x $max_len;
	    for my $v (split(/ /, $vars)) {
		if ($v =~ /^input0_(\d+)=(0x[0-9a-f]+)$/) {
		    $ce[$1] = hex $2;
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
	return (0, pack("C*", @ce));
    }
}

# Given a set of tests, run with the adaptor symbolic to see if we can
# synthesize an adaptor that works for those tests.
sub try_synth {
    my($testsr) = @_;
    open(TESTS, ">tests");
    for my $t (@$testsr) {
	my $buf = "\0" x 64;
	substr($buf, 0, length($t)) = $t;
	print TESTS $buf;
    }
    close TESTS;
    my @args = ($fuzzball, "-linux-syscalls", "-arch", "x64", $bin,
		@solver_opts, "-fuzz-start-addr", $main_addr,
		@sym_field_opts,
		"-trace-iterations", "-trace-assigns", "-solve-final-pc",
		"-branch-preference", "$match_jne_addr:1",
		#"-trace-conditions", "-trace-temps", "-omit-pf-af",
		"-random-seed", int(rand(10000000)),
		"--", $bin, "f", "tests");
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

my $zero_adapt = join(",", map(sprintf("%02x", $_), (0) x 256));
my $base_adapt = join(",", map(sprintf("%02x", $_), 0 .. 255));
my $good_adapt = join(",", map(sprintf("%02x", $_), 0 .. 9, 0, 11 .. 255));

#my $samp = try_synth(["a", "ab", "bc", "cd", "de", "ef", "fg", "gh",
#		      "aba", "abcdefghgfedcba", "a\n"]);
#print "Synthesized $samp\n";
#exit;

# Main loop: starting with a stupid adaptor and no tests, alternate
# between test generation and synthesis.
my $adapt = $zero_adapt;
my @tests = ();
my $done = 0;
while (!$done) {
    print "Checking $adapt:\n";
    my($res, $ces) = check_adaptor($adapt);
    if ($res) {
	print "Success!\n";
	print "Final test set:\n";
	for my $t (@tests) {
	    print " ", escape_str($t), "\n";
	}
	print "Final adaptor is $adapt\n";
	$done = 1;
	last;
    } else {
	my $escaped = escape_str($ces);
	print "Mismatch on input $escaped; adding as test\n";
	push @tests, $ces;
    }

    $adapt = try_synth(\@tests);
    print "Synthesized adaptor $adapt\n";
}
