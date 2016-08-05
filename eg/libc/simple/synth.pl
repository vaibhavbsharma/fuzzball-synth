use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $const_lb = -1;
my $const_ub = 7;
my $hard_timeout = 120; #seconds
my $rand_seed = 1;
my $default_adaptor = 1;

die "Usage: synth.pl <bucket number ( 1 - 16 ) <direction ( 1 or -1 )>" unless @ARGV == 2;
my($bucket_num, $direction) = @ARGV;

my $total_fns = 1316;
my @boundaries;
for my $i (0 .. 16) {
    push @boundaries, int($i * $total_fns/16);
}
$boundaries[0]=-1;

my $start_lim = $boundaries[$bucket_num-1]+1;
my $end_lim = $boundaries[$bucket_num];
printf "start_lim = $start_lim end_lim = $end_lim number of functions = %d\n", $end_lim-$start_lim;

for (my $f1num = $start_lim; $f1num <= $end_lim; $f1num++) {
    for (my $f2_limit=1; $f2_limit <= 10; $f2_limit++) {
	my $f2num = $f1num + ($f2_limit * $direction);
	if ($f2num > 1315 || $f2num < 0) {
	    next;
	}
	print "Startin synthesis for $f1num and $f2num\n";
	
	my @cmd = ("perl synth-one.pl",
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
