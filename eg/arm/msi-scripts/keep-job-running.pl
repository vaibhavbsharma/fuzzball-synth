#!/usr/bin/perl

use strict;

die "Usage: keep-job-running.pl <.qsub file name> <dir at itasca where .qsub file is located>"
  unless @ARGV == 2;

my ($job_name,$dir) = @ARGV;

if( substr($job_name, length($job_name)-5) =~ ".qsub") {
    $job_name = substr($job_name, 0, length($job_name)-5);
}

my $start_bucket=-1;
if(substr($job_name,length($job_name)-1,1) eq "1") { $start_bucket = 1; }
elsif(substr($job_name,length($job_name)-1,1) eq "2") { $start_bucket = 9; } 

if($start_bucket == -1) {
    die "not sure which half we're running on";
}

my $output;
while(1) {
    my $not_done = 0;
    for(my $i = $start_bucket; $i <= $start_bucket + 7; $i++) {
	$output = `ssh itasca "file $dir/arm-$i/done$i"`;
	if(index($output, "No such file") != -1) {
	    $not_done++;
	}
    }
    if($not_done == 0) {
	print "done running all buckets\n";
	exit(0);
    }
    $output = `ssh itasca "qstat -u vaibhav -f"`;
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection timed out") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    my $found = 0;
    if(index($output, $job_name) != -1) { $found = 1; }
# printf("found = $found\n");
    if($found == 0) {
	my $output= `ssh itasca "qsub $dir/$job_name.qsub"`;
	my $now_string = localtime;
	printf("new job queued: output = $output at time = %s\n", $now_string);
    }
    sleep 120;
}
