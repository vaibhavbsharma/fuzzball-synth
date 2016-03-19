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
	    } elsif ($a eq "ENTRY") {
		# Two-pointer struct, passed like two arguments
		$int_args += 2;
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

# The information in a C prototype for a varargs function isn't
# specific enough to match up with what our analysis reports. The
# explicit arguments are guaranteed to be there, but it doesn't
# predict how many variable arguments might be passed, or whether any
# of the variable arguments will be in vector registers (e.g.,
# floating point). Also, only if there might be vector registers will
# %al be checked for their count. So here we record for each function
# the maximum total number of integer-register arguments and the
# maximum total number of vector-register arguments. -1 means unlimited.
my %varargs_info =
  (
   # Execl-family functions can have a lot of integer args
   "execl"  => [-1, 0],
   "execlp" => [-1, 0],
   "execle" => [-1, 0],
   # Printf family functions can take lots of args of both kinds
   # Printf-subfamily: error reporting
   "syslog"        => [-1, -1],
   "warn"          => [-1, -1],
   "warnx"         => [-1, -1],
   "err"           => [-1, -1],
   "errx"          => [-1, -1],
   "error"         => [-1, -1],
   "error_at_line" => [-1, -1],
   "argp_failure"  => [-1, -1],
   "argp_error"    => [-1, -1],
   # Printf-like functions with "printf" but no "v" in the name:
   "fprintf"        => [-1, -1],
   "printf"         => [-1, -1],
   "snprintf"       => [-1, -1],
   "sprintf"        => [-1, -1],
   "asprintf"       => [-1, -1],
   "dprintf"        => [-1, -1],
   "obstack_printf" => [-1, -1],
   "swprintf"       => [-1, -1],
   "fwprintf"       => [-1, -1],
   "wprintf"        => [-1, -1],
   # Printf-like family: strfmon, takes doubles only
   "strfmon"       => [3, -1],
   "strfmon_l"     => [4, -1],
   # Scanf family functions are a special case: they don't actually
   # take any float variable arguments, but because the glibc wrapper
   # implementation is a separate function, GCC is unable to optimize
   # the SSE register saving away.
   "fscanf" =>  [-1, 0],
   "scanf" =>   [-1, 0],
   "sscanf" =>  [-1, 0],
   "swscanf" => [-1, 0],
   "wscanf" =>  [-1, 0],
   "fwscanf" => [-1, 0],
   # System-call-related varargs functions
   "syscall" => [7, 0],
   "clone"   => [7, 0],
   "mremap"  => [5, 0],
   "prctl"   => [5, 0],
   "semctl"  => [4, 0],
   "open"    => [3, 0],
   "openat"  => [4, 0],
   "fcntl"   => [3, 0],
   "ulimit"  => [2, 0],
   "ioctl"   => [3, 0],
   "ptrace"  => [4, 0],
  );

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

sub format_reg_color {
    my($r, $seen_r, $wanted_r) = @_;
    if ($seen_r->{$r} and $wanted_r->{$r}) {
	return $r; # True positive: plain
    } elsif (!$seen_r->{$r} and !$wanted_r->{$r}) {
	return " " x length($r); # True negative: blank
    } elsif ($seen_r->{$r} and !$wanted_r->{$r}) {
	return "\e[01;31m$r\e[0m"; # False positive: bold red
    } elsif (!$seen_r->{$r} and $wanted_r->{$r}) {
	return "\e[01;36m$r\e[0m"; # False negative: bold cyan
    }
}

sub format_regs_color {
    my($seen_r, $wanted_r) = @_;
    my %seen = %$seen_r;
    my %wanted = %$wanted_r;
    my @std_args = ("rdi", "rsi", "rdx", "rcx", "r8", "r9");
    my $std_args = join(" ", map(format_reg_color($_, $seen_r, $wanted_r),
				 @std_args));
    my %both = (%seen, %wanted);
    delete @both{@std_args};
    return join(" ", $std_args, map(format_reg_color($_, $seen_r, $wanted_r),
				    sort keys %both));
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

my @preserved_regs = qw(r12 r13 r14 r15 rbp rbx);
my @int_args_regs = qw(rdi rsi rdx rcx r8 r9);

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
    my($va_int_max, $va_fp_max);
    my $is_fp_va = 0;
    my @expected_regs = ();
    if ($name =~ /^_?setjmp/) {
	@expected_regs = ("rdi", @preserved_regs);
    } elsif ($name =~ /^(get|swap)context$/) {
	@expected_regs = (@int_args_regs, @preserved_regs);
    } elsif ($name eq "makecontext") {
	@expected_regs = @int_args_regs;
    } elsif ($name eq "mcount") {
	@expected_regs = ("rbp");
    } elsif ($is_varargs) {
	if (exists $varargs_info{$name}) {
	    ($va_int_max, $va_fp_max) = @{$varargs_info{$name}};
	    if ($va_int_max == -1) {
		$va_int_max = 6;
	    }
	    $int_args = $va_int_max;
	    if ($va_fp_max == -1) {
		$va_fp_max = 8;
	    }
	    $is_fp_va = 1 if $va_fp_max > $fp_args;
	    $fp_args = $va_fp_max;
	} else {
	    die "Missing varargs_info for $name\n";
	}
    }
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
    push @expected_regs, "xmm6" if $fp_args >= 7;
    push @expected_regs, "xmm7" if $fp_args >= 8;
    push @expected_regs, "rax" if $is_fp_va;
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
    if (0) {
	printf "%30s: (%8.3f%s%s%3d/%3d) %s\n", $name, $time, $tout,
	  ($fail ? "F" : " "), $rets, $paths, format_regs(@regs);
	print " " x 52, format_regs(@expected_regs), "\n";
    } else {
	printf "%30s: (%8.3f%s%s%3d/%3d) %s\n", $name, $time, $tout,
	  ($fail ? "F" : " "), $rets, $paths,
	    format_regs_color(\%seen_set, \%expected_set);
    }
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
