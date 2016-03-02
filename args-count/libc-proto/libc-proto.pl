#!/usr/bin/perl

use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $fuzzball = "../../../../tools/fuzzball/exec_utils/fuzzball";
my $stp = "../../../../tools/fuzzball/stp/stp";
my $z3 = "./z3";
my $load_base = 0x400000;

my $types = "types.dat";
my $ldso = "ld-linux-x86-64.so.2";
my $libc = "libc-2.19.so";
my $hard_timeout = 30; # seconds

my @funcs;
#@funcs = ("abs", "labs", "llabs");
#@funcs = ("div", "ldiv", "lldiv");
#@funcs = ("sleep");
#@funcs = ("malloc");
#@funcs = ("tolower");
#@funcs = ("openlog");
#@funcs = ("syslog");
#@funcs = ("syscall");
#@funcs = ("mmap");
#@funcs = ("connect");
#@funcs = ("hcreate_r");
#@funcs = ("hsearch");
#@funcs = ("endmntent");
#@funcs = ("isinf");

if (@ARGV) {
    @funcs = @ARGV;
}

my $solver;
if (-e $z3) {
    $solver = $z3;
} elsif (-e $stp) {
    $solver = $stp;
} else {
    die "Couldn't find a suitable SMT solver";
}

my @base_args = ("-arch", "x64");
my @state_args = ("-symbolic-regs",
		  "-initial-rsp", "0xbfff0000",
		  "-store-long", "0xbfff0000=0x00000000c0000000",
		  "-store-long", "0xc0000000=0x9090909090909090",
		  "-store-long", "0xc0000008=0x9090909090909090",
		  "-store-long", "0xc0000010=0x9090909090909090",
		  "-fuzz-end-addr", "0xc0000001");
my @trace_args = ("-trace-stopping", "-trace-iterations",
		  "-trace-loads", "-trace-stores",
		  "-trace-temps", "-omit-pf-af",
		  "-trace-conditions",
		  "-trace-sym-addrs",
		  "-tracepoint", "0xc0000000:R_RAX:reg64_t");
my @solver_args = ("-solver-path", $solver,
		   "-solver", "smtlib",
		   "-solver-timeout", 10);
my @limit_args = ("-num-paths", 100,
		  "-iteration-limit", 1000);
#my @syscall_args = ("-linux-syscalls",
#		    "-stop-on-symbolic-syscall-args",
#		    "-symbolic-syscall-error", 38); # ENOSYS
my @syscall_args = ();

my %sym2addr;
open(NM, "nm -n $libc |") or die;
while (<NM>) {
    next unless /^([0-9a-f]{16}) (.) (.*)$/;
    my($addr, $type, $name) = (hex($1), $2, $3);
    if ($addr != 0) {
	$sym2addr{$name} = $addr;
    }
}
close NM;

my @known_funcs;
my %known_funcs;
my @func_info;
open(F, "<", $types) or die;
while (<F>) {
    my($num, $nargs, $name, $type) = split(" ", $_, 4);
    push @func_info, [$num, $nargs, $name, $type];
    $known_funcs{$name} = 1;
    push @known_funcs, $name;
}
close F;

if (not @funcs) {
    #@funcs = sort keys %known_funcs; # alphabetical order
    @funcs = @known_funcs; # address order
}

for my $func (@funcs) {
    my $addr = $sym2addr{$func};
    my $start_addr = $load_base + $addr;
    my @cmd = ($fuzzball, @base_args, @state_args, @trace_args,
	       @solver_args, @limit_args, @syscall_args,
	       "-start-addr", sprintf("0x%x", $start_addr),
	       $libc);
    if (@funcs == 1) {
	print "@cmd\n";
    }
    printf "%30s: ", $func;
    my $start_time = time();
    my $timed_out = 0;
    my %seen;
    eval {
	local $SIG{ALRM} = sub { die "alarm\n" };
	alarm $hard_timeout;
	open(LOG, "-|", @cmd) or die;
	while (<LOG>) {
	    if (/^(Store to|Load from) conc\. mem bff..... = initial_\w+_\d+:reg64_t/) {
		# Ignore saves and restores of unmodified registers
		# on the stack
		next;
	    } elsif (/^At c0000000, R_RAX:reg64_t is /) {
		s/initial_rax//g;
		# Ignore the "use" of %rax in the final %rax value
		next;
	    }
	    #print $_;
	    $seen{"rdi"}++ if /initial_rdi/;
	    $seen{"rsi"}++ if /initial_rsi/;
	    $seen{"rdx"}++ if /initial_rdx/;
	    $seen{"rcx"}++ if /initial_rcx/;
	    $seen{"r8"}++ if /initial_r8/;
	    $seen{"r9"}++ if /initial_r9/;
	    $seen{"rax"}++ if /initial_rax/;
	    $seen{"rbx"}++ if /initial_rbx/;
	    $seen{"rbp"}++ if /initial_rbp/;
	    $seen{"r10"}++ if /initial_r10/;
	    $seen{"r11"}++ if /initial_r11/;
	    $seen{"r12"}++ if /initial_r12/;
	    $seen{"r13"}++ if /initial_r13/;
	    $seen{"r14"}++ if /initial_r14/;
	    $seen{"r15"}++ if /initial_r15/;
	    $seen{"xmm0"}++ if /initial_ymm0_0/;
	    $seen{"xmm1"}++ if /initial_ymm1_0/;
	    $seen{"xmm2"}++ if /initial_ymm2_0/;
	    $seen{"xmm3"}++ if /initial_ymm3_0/;
	    $seen{"xmm4"}++ if /initial_ymm4_0/;
	    $seen{"xmm5"}++ if /initial_ymm5_0/;
	}
	close LOG;
	alarm 0;
    };
    if ($@ eq "alarm\n") {
	close LOG;
	$timed_out = 1;
    }
    my $end_time = time();
    my $time = $end_time - $start_time;
    printf "(%8.3f%s) ", $time, ($timed_out ? "T" : "");
    my $std_args = join(" ",
			($seen{"rdi"} ? "rdi" : "   "),
			($seen{"rsi"} ? "rsi" : "   "),
			($seen{"rdx"} ? "rdx" : "   "),
			($seen{"rcx"} ? "rcx" : "   "),
			($seen{"r8"}  ? "r8" :  "  "),
			($seen{"r9"}  ? "r9" :  "  "));
    delete @seen{"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    print join(" ", $std_args, sort keys %seen), "\n";
}
