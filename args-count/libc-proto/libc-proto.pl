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
my $hard_timeout = 60; # seconds
my $iters_limit = 300;

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
		  "-initial-rsp", "0xbfff0008",
		  "-store-long", "0xbfff0008=0x00000000c0000000",
		  "-store-long", "0xc0000000=0x9090909090909090",
		  "-store-long", "0xc0000008=0x9090909090909090",
		  "-store-long", "0xc0000010=0x9090909090909090",
		  "-fuzz-end-addr", "0xc0000001");
my @trace_args = ("-trace-stopping",
		  "-trace-iterations", "-trace-completed-iterations",
		  #"-trace-loads", "-trace-stores",
		  "-track-sym-usage",
		  "-tracepoint", "0xc0000000:R_RAX:reg64_t");
my @solver_args = ("-solver-path", $solver,
		   "-solver", "smtlib",
		   "-solver-timeout", 10,
		   "-ite-ivc",
		  );
my @limit_args = ("-num-paths", $iters_limit,
		  "-iteration-limit", 1000);
#my @syscall_args = ("-linux-syscalls",
#		    "-stop-on-symbolic-syscall-args",
#		    "-symbolic-syscall-error", 38); # ENOSYS
my @syscall_args = ("-noop-syscalls", "-trace-syscalls");

# Thread-local-data storage locations
# objdump -R libc-2.19.so| fgrep TPOFF
# then read the actual values with GDB
my @tsd_locs =
  ([0x000,  -64],
   [0x008,   -8],
   [0x030, -176], # __libc_tsd_LOCALE
   [0x080, -112], # __libc_tsd_CTYPE_B
   [0x0d8,  -20],
   [0x0e8, -160],
   [0x158, -144],
   [0x1a0, -128],
   [0x200,  -16],
   [0x270, -168],
  );
my $tsd_got_base = 0x3bdd80; # .got
for my $l (@tsd_locs) {
    my $addr = $load_base + $tsd_got_base + $l->[0];
    my $val = $l->[1];
    push @state_args, "-store-long", sprintf("0x%08Lx=%d", $addr, $val);
}

# There's enough information in the binary to figure these out,
# (either here or inside FuzzBALL), so listing some of them here is
# just a stopgap. Though some of them need to link to ld.so, not
# just inside libc, which makes things more complicated.
my @got_locs =
  (
   # Dynamically linked functions
   [0x3be018, 0x082e50], # realloc
   [0x3be020, 0x0826b0], # malloc
   #[0x3be028, 0x000000], # __tls_get_addr, ld.so?
   [0x3be030, 0x083170], # memalign
   #[0x3be038, 0x000000], # _dl_find_dso_for_object, ld.so?
   [0x3be040, 0x083180], # calloc
   [0x3be048, 0x082d50], # free

   # GOT data pointers
   [0x3bdf40, 0x3bf870], # stdout
   [0x3bf870, 0x3bf400], #_IO_2_1_stdout_
   [0x3bded0, 0x3be720], # __memalign_hook
   [0x3bdee0, 0x3be740], # __malloc_hook
   [0x3bdea8, 0x3c14a0], # environ

   # Relocations
   [0x3be720, 0x083bf0], # memalign_hook_ini
   #[0x3be740, 0x083b50], # __malloc_hook related
   [0x3be740, -$load_base], # __malloc_hook related: 0 = no hook?
  );
for my $l (@got_locs) {
    my $addr = $load_base + $l->[0];
    my $val = $load_base + $l->[1];
    push @state_args, "-store-long", sprintf("0x%08Lx=0x%Lx", $addr, $val);
}

my %sym2addr;
my %sym2type;
open(NM, "nm -nD $libc |") or die;
while (<NM>) {
    next unless /^([0-9a-f]{16}) (.) (.*)$/;
    my($addr, $type, $name) = (hex($1), $2, $3);
    if ($addr != 0) {
	$sym2addr{$name} = $addr;
	$sym2type{$name} = $type;
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
    die "Unrecognized function $func" unless exists $sym2addr{$func};
    my $addr = $sym2addr{$func};
    next if $sym2type{$func} eq "i"; # Not supported yet
    my $start_addr = $load_base + $addr;
    my @cmd = ($fuzzball, @base_args, @state_args, @trace_args,
	       @solver_args, @limit_args, @syscall_args,
	       "-start-addr", sprintf("0x%x", $start_addr),
	       $libc);
    if (@funcs == 1) {
	print "@cmd\n";
    }
    printf "%20s: ", $func;
    my $start_time = time();
    my $timed_out = 0;
    my %seen;
    my($iters_started, $iters_returned, $iters_finished) = (0, 0, 0);
    eval {
	local $SIG{ALRM} = sub { die "alarm\n" };
	alarm $hard_timeout;
	open(LOG, "-|", @cmd) or die;
	while (<LOG>) {
	    if (/^Iteration (\d+):/) {
		$iters_started = $1;
	    } elsif (/^Iteration (\d+) completed/) {
		$iters_finished = $1;
	    }
 	    if (/^(Store to|Load from) /) {
		# Ignore the output of -trace-loads and -trace-stores.
		# Register usage in the loaded/stored value is now tracked
		# with -track-sym-usage, but it's nice to still be able
		# to turn the options on for debugging.
 		next;
	    } elsif (/^Occurrence of /) {
		# This message represents a syntactic occurence, but
		# later FuzzBALL will check whether it's semantically
		# relevant.
		next;
 	    } elsif (/^At c0000000, R_RAX:reg64_t is /) {
		s/initial_rax//g;
		# Ignore the "use" of %rax in the final %rax value
		$iters_returned++;
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
	    $seen{"xmm6"}++ if /initial_ymm6_0/;
	    $seen{"xmm7"}++ if /initial_ymm7_0/;
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
    my $iters;
    if ($iters_finished == $iters_limit) {
	$iters = $iters_limit + 1;
    } else {
	$iters = $iters_started;
    }
    printf "(%8.3f%s%3d/%3d) ", $time, ($timed_out ? "T" : " "),
      $iters_returned, $iters;
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
