use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $const_lb = -1;
my $const_ub = 7;
my $hard_timeout = 120; #seconds
my $rand_seed = 4;
my $default_adaptor = 1;

#die "Usage: synth.pl <f1num> <f2num> <seed> <default adaptor(0=zero,1=identity) [<lower bound for constant> <upper bound for constant>]"
#  unless @ARGV == 6;
#my($f1num, $f2num, $rand_seed, $default_adaptor, $const_lb, $const_ub) = @ARGV;

my $lim0 = -1;
my $lim1 = 327;
my $lim2 = 657;
my $lim3 = 984;
my $lim4 = 1315;

my $start_lim = $lim0 + 1;
my $end_lim = $lim4;
my $direction = 1;

my @fnums=(1055,1056,1057,1058, 678,679, 1061);
#wait,waitpid,wait3,wait4, labs,llabs, sleep

for (my $_f1num = 0; $_f1num <= 6; $_f1num++) {
    for (my $_f2num=0; $_f2num<= 6; $_f2num++) {
	if ($_f1num == $_f2num) {
	    next;
	}
	my $f1num=$fnums[$_f1num];
	my $f2num=$fnums[$_f2num];
	#print "Startin synthesis for $f1num and $f2num\n";
	
	my @cmd = ("perl synth-one.pl",
		   sprintf("%d %d %d %d %d %d",
			   $f1num,$f2num,$rand_seed,
			   $default_adaptor,
			   $const_lb,$const_ub),"2>&1");
	
	my $pid=0;
	eval {
	    local $SIG{ALRM} = sub { die "alarm\n" };
	    alarm $hard_timeout;
	    #print "@cmd\n";
	    $pid = open(LOG, "-|", join(" ",@cmd)) or die "Failed to execute command";
	    while (<LOG>) {
		print $_;
		next;
	    }
	    close LOG;
	    alarm 0;
	};
	#print "*******Stopped******\n";
	print $@;
	#print "*******Stopped******\n";
	if ($@ eq "alarm\n") {
	    #print "calling close LOG\n";
	    kill 'TERM',$pid;
	    close LOG or warn $! ? "Error closing pipe: $!":"Exit status $? from close";
	    #print "killed by alarm\n";
	}
    }
}
