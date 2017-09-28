#!/usr/bin/perl

use strict;

die "Usage: report-metrics.pl <log file name> <number of bucket directories> <base dir. absolute path>"
  unless @ARGV == 3;
my($log_file_name,$num_dirs,$dir_path) = @ARGV;

my @timeout_time = ();
my @timeout_steps = ();
my @timeout_solver = ();
my @timeout_stopped_during = ();

my @adaptor_time = ();
my @adaptor_steps = ();
my @adaptor_solver = ();

my @inequiv_time = ();
my @inequiv_steps = ();
my @inequiv_solver = ();

my @fatal_time = ();
my @fatal_steps = ();
my @fatal_solver = ();

my @ce_fail_time = ();
my @ce_fail_steps = ();
my @ce_fail_solver = ();

sub calc_average_1 {
    my @arr = @{$_[0]};
    my ($sum1,$count) = (0,0);
    foreach my $val (@arr) {
	my ($val1) = $val;
	$sum1 += $val1; $count++;
    }
    return ($sum1/$count);
}

sub calc_average_3 {
    my @arr = @{$_[0]};
    my ($sum1,$sum2,$sum3,$count) = (0,0,0,0);
    for(my $i=0; $i < scalar(@arr); $i+=3) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
	$sum1 += $val1; $sum2 += $val2; $sum3 += $val3; $count++;
    }
    if($count > 0) {
	return ($sum1/$count,$sum2/$count,$sum3/$count);
    } else { return (0,0,0); }
}

sub calc_average_4 {
    my @arr = @{$_[0]};
    my ($sum1,$sum2,$sum3,$sum4,$count) = (0,0,0,0,0);
    for(my $i=0; $i < scalar(@arr); $i+=4) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
	my $val4 = $arr[$i+3];
	$sum1 += $val1; $sum2 += $val2; $sum3 += $val3; $sum4 += $val4;
	$count++;
    }
    if($count > 0) {    
	return ($sum1/$count,$sum2/$count,$sum3/$count,$sum4/$count);
    } else { return (0,0,0); }
}

sub calc_average_5 {
    my @arr = @{$_[0]};
    my ($sum1,$sum2,$sum3,$sum4,$sum5,$count) = (0,0,0,0,0,0);
    for(my $i=0; $i < scalar(@arr); $i+=5) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
	my $val4 = $arr[$i+3];
	my $val5 = $arr[$i+4];
	$sum1 += $val1; $sum2 += $val2; $sum3 += $val3; 
	$sum4 += $val4; $sum5 += $val5;
	$count++;
    }
    if($count > 0) {    
	return ($sum1/$count,$sum2/$count,$sum3/$count,$sum4/$count,$sum5/$count);
    } else { return (0,0,0); }
}

for(my $i=1; $i <= $num_dirs; $i++) {
    open(LOG,"<$dir_path/arm-$i/logs/$log_file_name");
    my ($result,$count) = (-1,0);
    while(<LOG>) {
	if(/^found timeout$/) { $result = 0; next; }
	if(/^found an adaptor$/) { $result = 1; next; }
	if(/^found inequivalence$/) { $result = 2; next; }
	if(/^found fatal error$/) { $result = 3; next; }
	if(/^found ce failure$/) { $result = 4; next; }
	if($result != -1 && /^cmd = .*$/) {
	    $result = -1;
	    $count = 0;
	}
	if($result >= 0 && $result <= 4 && $count < 4) {
	    $count++;
	    if(/^time \(ce-total,ce-last,as-total,as-last,ce-as-total\) = \((.*),(.*),(.*),(.*),(.*)\)$/ ) {
		my ($v1,$v2,$v3,$v4,$v5) = ($1,$2,$3,$4,$5);
		for($result) {
		    /0/ && do { push @timeout_time, ($v1,$v2,$v3,$v4,$v5); last; };
		    /1/ && do { push @adaptor_time, ($v1,$v2,$v3,$v4,$v5); last; };
		    /2/ && do { push @inequiv_time, ($v1,$v2,$v3,$v4,$v5); last; };
		    /3/ && do { push @fatal_time,   ($v1,$v2,$v3,$v4,$v5); last; };
		    /4/ && do { push @ce_fail_time, ($v1,$v2,$v3,$v4,$v5); last; };
		}
	    } elsif(/^total steps \(ce,as,total\) = \((.*),(.*),(.*)\)$/) {
		my ($v1,$v2,$v3) = ($1,$2,$3);
		for($result) {
		    /0/ && do { push @timeout_steps, ($v1,$v2,$v3); last; };
		    /1/ && do { push @adaptor_steps, ($v1,$v2,$v3); last; };
		    /2/ && do { push @inequiv_steps, ($v1,$v2,$v3); last; };
		    /3/ && do { push @fatal_steps,   ($v1,$v2,$v3); last; };
		    /4/ && do { push @ce_fail_steps, ($v1,$v2,$v3); last; };
		}
	    } elsif(/^solver times \(ce-total,ce-last,as-total,as-last\) = \((.*),(.*),(.*),(.*)\)$/) {
		my ($v1,$v2,$v3,$v4) = ($1,$2,$3,$4);
		for($result) {
		    /0/ && do { push @timeout_solver, ($v1,$v2,$v3,$v4); last; };
		    /1/ && do { push @adaptor_solver, ($v1,$v2,$v3,$v4); last; };
		    /2/ && do { push @inequiv_solver, ($v1,$v2,$v3,$v4); last; };
		    /3/ && do { push @fatal_solver,   ($v1,$v2,$v3,$v4); last; };
		    /4/ && do { push @ce_fail_solver, ($v1,$v2,$v3,$v4); last; };
		}
	    } elsif(/^stopped during (.*) with solver time = .*$/ && $result == 0) {
		if($1 =~ "Adaptor-Search") {
		    push @timeout_stopped_during, 1;
		} elsif($1 =~ "CounterExample-Search") {
		    push @timeout_stopped_during, 2;
		}
	    }
	} # end if result >= 0 && <= 4
    } # end while(<LOG>)
}

my ($t_st_ce_avg,$t_st_as_avg,$t_st_t_avg) = calc_average_3(\@timeout_steps);
print "$t_st_ce_avg, $t_st_as_avg, $t_st_t_avg\n";
my ($a_st_ce_avg,$a_st_as_avg,$a_st_t_avg) = calc_average_3(\@adaptor_steps);
print "$a_st_ce_avg, $a_st_as_avg, $a_st_t_avg\n";
my ($i_st_ce_avg,$i_st_as_avg,$i_st_t_avg) = calc_average_3(\@inequiv_steps);
print "$i_st_ce_avg, $i_st_as_avg, $i_st_t_avg\n";
my ($f_st_ce_avg,$f_st_as_avg,$f_st_t_avg) = calc_average_3(\@fatal_steps);
print "$f_st_ce_avg, $f_st_as_avg, $f_st_t_avg\n";
my ($cef_st_ce_avg,$cef_st_as_avg,$cef_st_t_avg) = calc_average_3(\@ce_fail_steps);
print "$cef_st_ce_avg, $cef_st_as_avg, $cef_st_t_avg\n";

my ($t_so_ce_avg,$t_so_as_avg,$t_so_t_avg) = calc_average_4(\@timeout_solver);
print "$t_so_ce_avg, $t_so_as_avg, $t_so_t_avg\n";
my ($a_so_ce_avg,$a_so_as_avg,$a_so_t_avg) = calc_average_4(\@adaptor_solver);
print "$a_so_ce_avg, $a_so_as_avg, $a_so_t_avg\n";
my ($i_so_ce_avg,$i_so_as_avg,$i_so_t_avg) = calc_average_4(\@inequiv_solver);
print "$i_so_ce_avg, $i_so_as_avg, $i_so_t_avg\n";
my ($f_so_ce_avg,$f_so_as_avg,$f_so_t_avg) = calc_average_4(\@fatal_solver);
print "$f_so_ce_avg, $f_so_as_avg, $f_so_t_avg\n";
my ($cef_so_ce_avg,$cef_so_as_avg,$cef_so_t_avg) = calc_average_4(\@ce_fail_solver);
print "$cef_so_ce_avg, $cef_so_as_avg, $cef_so_t_avg\n";

my ($t_tm_ce_avg,$t_tm_as_avg,$t_tm_t_avg) = calc_average_5(\@timeout_time);
print "$t_tm_ce_avg, $t_tm_as_avg, $t_tm_t_avg\n";
my ($a_tm_ce_avg,$a_tm_as_avg,$a_tm_t_avg) = calc_average_5(\@adaptor_time);
print "$a_tm_ce_avg, $a_tm_as_avg, $a_tm_t_avg\n";
my ($i_tm_ce_avg,$i_tm_as_avg,$i_tm_t_avg) = calc_average_5(\@inequiv_time);
print "$i_tm_ce_avg, $i_tm_as_avg, $i_tm_t_avg\n";
my ($f_tm_ce_avg,$f_tm_as_avg,$f_tm_t_avg) = calc_average_5(\@fatal_time);
print "$f_tm_ce_avg, $f_tm_as_avg, $f_tm_t_avg\n";
my ($cef_tm_ce_avg,$cef_tm_as_avg,$cef_tm_t_avg) = calc_average_5(\@ce_fail_time);
print "$cef_tm_ce_avg, $cef_tm_as_avg, $cef_tm_t_avg\n";

print "Average# timeout stops = ", calc_average_1(\@timeout_stopped_during), 
    ", (1=AS,2=CE)\n";

print "Adaptor times:\n";
my @arr = @adaptor_time;
for(my $i=0; $i < scalar(@arr); $i+=5) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
	my $val4 = $arr[$i+3];
	my $val5 = $arr[$i+4];
  print "$val5\n";
}
print "Adaptor steps:\n";
my @arr = @adaptor_steps;
for(my $i=0; $i < scalar(@arr); $i+=3) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
  print "$val3\n";
}
print "Timeout steps:\n";
my @arr = @timeout_steps;
for(my $i=0; $i < scalar(@arr); $i+=3) {
	my $val1 = $arr[$i];
	my $val2 = $arr[$i+1];
	my $val3 = $arr[$i+2];
  print "$val3\n";
}
