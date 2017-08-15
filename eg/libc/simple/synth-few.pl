use strict;
use Time::HiRes qw(time alarm);
$| = 1;

my $const_lb = -1;
my $const_ub = 10;
my $hard_timeout = 1800; #seconds
my $rand_seed = 4;
my $default_adaptor = 1;

my @f1nums=(1055,1055,1055,1056,1057, 678,679, 796,797, 72, 1088, 855,856, 681,682, 904);
my @f2nums=(1056,1057,1058,1058,1058, 679,678, 797,796, 73, 1086, 856,855, 682,681, 905);
for (my $_fnum = 0; $_fnum <= $#f1nums; $_fnum++) {
	my $f1num=$f1nums[$_fnum];
	my $f2num=$f2nums[$_fnum];
	print "Startin synthesis for $f1num and $f2num\n";
	
	my @cmd = ("perl synth-typeconv.pl",
		   sprintf("%d %d %d %d %d %d",
			   $f1num,$f2num,$rand_seed,
			   $default_adaptor,
			   $const_lb,$const_ub),"2>&1");
	
	print "@cmd\n";
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
	print "*******Stopped******\n";
	print $@;
	print "*******Stopped******\n";
	if ($@ eq "alarm\n") {
	    print "calling close LOG\n";
	    kill 'TERM',$pid;
	    close LOG or warn ${!} ? "Error closing pipe: $!":"Exit status $? from close";
	    print "killed by alarm\n";
	}
    #exit;
}

my @f1nums=( 663,664,663,662,664 );
my @f2nums=( 664,663,707,707,1323);
for (my $_fnum = 0; $_fnum <= $#f1nums; $_fnum++) {
	my $f1num=$f1nums[$_fnum];
	my $f2num=$f2nums[$_fnum];
	print "Startin synthesis for $f1num and $f2num\n";
	
	my @cmd = ("perl synth-argsub.pl",
		   sprintf("%d %d %d %d %d %d",
			   $f1num,$f2num,$rand_seed,
			   $default_adaptor,
			   $const_lb,$const_ub),"2>&1");
	
	print "@cmd\n";
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
	print "*******Stopped******\n";
	print $@;
	print "*******Stopped******\n";
	if ($@ eq "alarm\n") {
	    print "calling close LOG\n";
	    kill 'TERM',$pid;
	    close LOG or warn ${!} ? "Error closing pipe: $!":"Exit status $? from close";
	    print "killed by alarm\n";
	}
    #exit;
}
