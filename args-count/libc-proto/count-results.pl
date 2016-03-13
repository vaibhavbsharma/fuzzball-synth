#!/usr/bin/perl

use strict;

my $types = "types.dat";

my @known_funcs;
my %func_info;
my @func_info;
open(F, "<", $types) or die;
while (<F>) {
    my($num, $nargs, $name, $type) = split(" ", $_, 4);
    my($int_args, $fp_args) = (0, 0);
    my $is_varargs = 0;
    chomp $type;
    my $type2 = $type;
    $type2 =~ s/ __attribute__\(\(noreturn\)\)//;
    $type2 =~ /^[^\(]+\((.*)\) *$/ or die "Bad <$type2>";
    my $args = $1;
    while (($args =~ tr/(/(/) > 0) {
        $args =~ s/\([^()]*\)//;
    }
    my @args = split(/, /, $args);
    if ($args[$#args] eq "...") {
	pop @args;
	$is_varargs = 1;
	$num =~ s/\+//;
    }
    if (@args == 1 and $args[0] eq "void") {
	($int_args, $fp_args) = (0, 0);
    } else {
	die "Wrong num $nargs (@args)" unless @args == $nargs;
	for my $a (@args) {
	    if ($a eq "float" or $a eq "double") {
		$fp_args++;
	    } else {
		$int_args++;
	    }
	}
    }
    #printf "%d %d %s\n", $int_args, $fp_args, $name;
    my $info = [$num, $nargs, $name, $type, $int_args, $fp_args, $is_varargs];
    push @func_info, $info;
    $func_info{$name} = $info;
    push @known_funcs, $name;
}
close F;

sub format_regs {
    my(@regs) = @_;
    my %seen;
    @seen{@regs} = (1) x @regs;
    my $std_args = join(" ",
			($seen{"rdi"} ? "rdi" : "   "),
			($seen{"rsi"} ? "rsi" : "   "),
			($seen{"rdx"} ? "rdx" : "   "),
			($seen{"rcx"} ? "rcx" : "   "),
			($seen{"r8"}  ? "r8" :  "  "),
			($seen{"r9"}  ? "r9" :  "  "));
    delete @seen{"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    return join(" ", $std_args, sort keys %seen);
}

my $strange_terms = 0;
my $solver_touts = 0;
my $div_zeros = 0;
my $bad_insns = 0;
my $hard_touts = 0;
my $pathouts = 0;
my $completes = 0;

my $args_seen = 0;
my $args_expected = 0;
my $args_fn = 0;
my $args_match = 0;
my $args_fp = 0;

my $num_funcs = 0;
my $total_time = 0;

while (<>) {
    if (/^(\s*(\w+): )$/) {
	print "Incomplete at $2\n";
	last;
    }
    /^(\s*(\w+): )([F\(].*)$/
	or die "Pre-parse failure on <$_>";
    $num_funcs++;
    my($pre, $name, $f) = ($1, $2, $3);
    my $line = $_;
    my $fail = 0;
    if ($f =~ /Fatal error/) {
	if ($f =~ /Strange term/) {
	    $strange_terms++;
	} elsif ($f =~ /SolverFailure/) {
	    $solver_touts++;
	} elsif ($f =~ /Division_by_zero/) {
	    $div_zeros++;
	} elsif ($f =~ /unhandled unknown Unrecognized binary op in cfold_with_type/) {
	    $bad_insns++;
	} else {
	    die "Unexpected fatal error $f";
	}
	$fail = 1;
	$line = $pre . scalar(<>);
    }
    $line =~ m{^\s*\w+: \(\s*(\d+\.\d+)([T ])(?:\s*(\d+)/)?\s*(\d+)\)([a-z0-9 ]+)}
	or die "parse failure on <$line>";
    my($time, $tout, $rets, $paths, $regs) = ($1, $2, $3, $4, $5);
    $total_time += $time;
    my @regs = split(" ", $regs);
    $args_seen += @regs;
    if ($tout eq "T") {
        $hard_touts++;
    } elsif ($paths == 301) {
	$pathouts++;
    } elsif (not $fail) {
	$completes++;
    }
    my $info = $func_info{$name};
    die unless $info;
    my($int_args, $fp_args, $is_varargs) = @$info[4, 5, 6];
    my @expected_regs = ();
    push @expected_regs, "rdi" if $int_args >= 1;
    push @expected_regs, "rsi" if $int_args >= 2;
    push @expected_regs, "rdx" if $int_args >= 3;
    push @expected_regs, "rcx" if $int_args >= 4;
    push @expected_regs, "r8"  if $int_args >= 5;
    push @expected_regs, "r9"  if $int_args >= 6;
    push @expected_regs, "xmm0" if $fp_args >= 1;
    push @expected_regs, "xmm1" if $fp_args >= 2;
    push @expected_regs, "xmm2" if $fp_args >= 3;
    push @expected_regs, "xmm3" if $fp_args >= 4;
    push @expected_regs, "xmm4" if $fp_args >= 5;
    push @expected_regs, "xmm5" if $fp_args >= 6;
    push @expected_regs, "rax" if $is_varargs;
    $args_expected += @expected_regs;
    my %seen_set;
    @seen_set{@regs} = (1) x @regs;
    my %expected_set;
    @expected_set{@expected_regs} = (1) x @expected_regs;
    my %either_set;
    @either_set{@regs} = (1) x @regs;
    @either_set{@expected_regs} = (1) x @expected_regs;
    for my $r (keys %either_set) {
	if ($seen_set{$r} and $expected_set{$r}) {
	    $args_match++;
	} elsif ($seen_set{$r} and not $expected_set{$r}) {
	    $args_fp++;
	} elsif ($expected_set{$r} and not $seen_set{$r}) {
	    $args_fn++;
	} else {
	    die "$name $r";
	}
    }
    printf "%30s: (%8.3f%s%s%3d/%3d) %s\n", $name, $time, $tout,
      ($fail ? "F" : " "), $rets, $paths, format_regs(@regs);
    print " " x 52, format_regs(@expected_regs), "\n";
}

print  "StrTerm SolvTO Div0 BadInsn HardTO PathO Compl\n";
printf "   %4d   %4d %4d    %4d   %4d  %4d  %4d\n",
    $strange_terms, $solver_touts, $div_zeros, $bad_insns, $hard_touts,
    $pathouts, $completes;
print "\n";
print  "Arguments:   seen    expected\n";
printf "            %5d       %5d\n", $args_seen, $args_expected;
print "\n";
print  "Arguments:  false pos.   matching   false neg.\n";
printf "                 %5d      %5d        %5d\n",
    $args_fp, $args_match, $args_fn;
print "\n";
printf "Num. funcs   Total time    Avg. time\n";
printf "      %4d    %8.3f     %8.3f\n",
  $num_funcs, $total_time, $total_time/$num_funcs;
