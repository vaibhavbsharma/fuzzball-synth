#!/usr/bin/perl

use strict;

die "Usage: keep-job-running.pl <.qsub file name> <dir at mesabi where .qsub file is located>"
  unless @ARGV == 2;

my ($job_name,$dir) = @ARGV;

if( substr($job_name, length($job_name)-5) =~ ".qsub") {
    $job_name = substr($job_name, 0, length($job_name)-5);
}

sub keep_job_running {
    my $job_name = shift(@_);
    my $start_bucket=-1;
    if(substr($job_name,length($job_name)-1,1) eq "1") { $start_bucket = 1; }
    elsif(substr($job_name,length($job_name)-1,1) eq "2") { $start_bucket = 9; } 
    elsif(substr($job_name,length($job_name)-1,1) eq "3") { $start_bucket = 17; } 
    elsif(substr($job_name,length($job_name)-1,1) eq "4") { $start_bucket = 24; } 

    if($start_bucket == -1) {
	die "not sure which half we're running on";
    }

    my $output;
    my $not_done = 0;
    for(my $i = $start_bucket; $i <= $start_bucket + 7; $i++) {
	$output = `ssh mesabi "file $dir/arm-$i/done$i"`;
	if(index($output, "No such file") != -1) {
	    $not_done++;
	}
    }
    if($not_done == 0) {
	print "done running all buckets for $job_name\n";
	return 1;
    }
    $output = `ssh mesabi "qstat -u vaibhav -f"`;
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection timed out") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    my $found = 0;
    if(index($output, $job_name) != -1) { $found = 1; }
# printf("found = $found\n");
    if($found == 0) {
	my $output= `ssh mesabi "qsub $dir/$job_name.qsub"`;
	my $now_string = localtime;
	printf("new job queued: output = $output at time = %s\n", $now_string);
    }
  return 0;
}

my ($done1,$done2,$done3,$done4) = (0,0,0,0);
while(1) {
    $done1 = keep_job_running($job_name . "-81");
    $done2 = keep_job_running($job_name . "-82");
    $done3 = keep_job_running($job_name . "-83");
    $done4 = keep_job_running($job_name . "-84");
    if($done1 == 1 && $done2 == 1 && $done3 == 1 && $done4 == 1) { 
	print "done running all buckets\n";
	exit(0); 
    }
    sleep 300;
}
