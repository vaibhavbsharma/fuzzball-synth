use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $hard_timeout = 120; #seconds
for (my $f1_num=0; $f1_num <= 1314; $f1_num++) {
    for (my $f2_limit=1; $f2_limit <= 2; $f2_limit++) {
	my $f2_num = $f1_num + $f2_limit;
	print "Startin synthesis for $f1_num and $f2_num\n";
	#my @cmd = ("ls ",sprintf("-ltr"));
	#my @cmd = ("perl","sleep-parent.pl");
	#my @cmd = ("perl synth-one.pl 0 ",sprintf("1 0"));
	my @cmd = ("perl synth-one.pl",sprintf("%d %d 0",$f1_num,$f2_num),"2>&1");
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
