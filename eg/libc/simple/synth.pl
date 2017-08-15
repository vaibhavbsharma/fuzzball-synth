use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $const_lb = -1;
my $const_ub = 7;
my $hard_timeout = 120; #seconds
my $rand_seed = 1;
my $default_adaptor = 1;
my $ifns_per_target = 10;
my $num_of_buckets = 8;

die "Usage: synth.pl <bucket number ( 1 - $num_of_buckets ) <direction ( 1 or -1 )>" unless @ARGV == 2;

my $bin = "./two-funcs";
print "compiling binary: ";
my $unused = `gcc -static two-funcs.c -g -o two-funcs -lpthread`;
my $gcc_ec = $?;
die "failed to compile $bin" unless $gcc_ec == 0;
print "gcc_ec = $gcc_ec\n";

# my $conc_adaptor_bin = "./two-funcs-conc";
# print "compiling concrete adaptor search binary: ";
# my $unused = `gcc $conc_adaptor_bin.c -g -o $conc_adaptor_bin -lpthread`;
# my $gcc_ec = $?;
# die "failed to compile $conc_adaptor_bin" unless $gcc_ec == 0;
# print "gcc_ec = $gcc_ec\n";

my($bucket_num, $direction) = @ARGV;

my $total_fns = 1316;
my @boundaries;
for my $i (0 .. $num_of_buckets) {
    push @boundaries, int($i * $total_fns/$num_of_buckets);
}
$boundaries[0]=-1;
my $start_lim = $boundaries[$bucket_num-1]+1;
my $end_lim = $boundaries[$bucket_num];
printf "start_lim = $start_lim end_lim = $end_lim number of functions = %d\n", $end_lim-$start_lim;

my $start_time=time();

for (my $f1num = $start_lim; $f1num < $end_lim; $f1num++) {
    for (my $f2_limit=1; $f2_limit <= $ifns_per_target; $f2_limit++) {
	my $f2num = $f1num + ($f2_limit * $direction);
	if ($f2num > $total_fns-1) {
	    $f2num = $f2num - $total_fns;
	    # next;
	} elsif ($f2num < 0) {
	    $f2num = $total_fns + $f2num;
	}
	print "Startin synthesis for $f1num and $f2num\n";
	
	my @cmd = ("perl synth-argsub.pl",
		   sprintf("%d %d %d %d %d %d",
			   $f1num,$f2num,$rand_seed,
			   $default_adaptor,
			   $const_lb,$const_ub),"2>&1");
	
	my $pid=0;
	eval {
	    local $SIG{ALRM} = sub { die "alarm\n" };
	    alarm $hard_timeout;
	    print "@cmd\n";
	    $pid = open(LOG, "-|", join(" ",@cmd)) or die "Failed to execute command";
	    while (<LOG>) {
		print $_;
		next;
	    }
	    close LOG;
	    alarm 0;
	};
	print "*******Stopped******\n";
	print $@;
	print "*******Stopped******\n";
	if ($@ eq "alarm\n") {
	    print "calling close LOG\n";
	    kill 'TERM',$pid;
	    close LOG or warn $! ? "Error closing pipe: $!":"Exit status $? from close";
	    print "killed by alarm\n";
	}
    }
}

my $diff = time() - $start_time;
print "total elapsed time = $diff\n";
