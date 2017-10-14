#!/usr/bin/perl

use strict;

die "Usage: keep-job-running.pl <.qsub file name> <dir at itasca where .qsub file is located>"
  unless @ARGV == 2;

my ($job_name,$dir) = @ARGV;

if( substr($job_name, length($job_name)-5) =~ ".qsub") {
    $job_name = substr($job_name, 0, length($job_name)-5);
}

sub keep_job_running {
    my $job_name = shift(@_);
	  my $job_num = shift(@_);
		$job_name = $job_name . "-8" . $job_num;
    my $start_bucket=($job_num-1)*8+1;
    
    if($start_bucket < 1 || $start_bucket > 16*8+1) {
	die "not sure which bucket we're running on";
    }

    my $output;
    my $not_done = 0;
    for(my $i = $start_bucket; $i <= $start_bucket + 15; $i++) {
	$output = `ssh itasca "file $dir/arm-$i/done$i"`;
	if(index($output, "No such file") != -1) {
	    $not_done++;
	}
    }
    if($not_done == 0) {
	print "done running all buckets for $job_name\n";
	return 1;
    }
    $output = `ssh itasca "qstat -u vaibhav -f"`;
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection timed out") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    my $found = 0;
    if(index($output, ($job_name . ".qsub")) != -1) { $found = 1; }
# printf("found = $found\n");
    if($found == 0) {
	my $output= `ssh itasca "qsub $dir/$job_name.qsub"`;
	my $now_string = localtime;
	printf("new job queued: output = $output at time = %s\n", $now_string);
    }
  return 0;
}

my ($done) = (0);
while(1) {
		for(my $j = 1; $j <= 16; $j+=2) {
	  my $ret = keep_job_running($job_name, $j);
    $done = $done && $ret;
		}
    if($done == 1) { 
	print "done running all buckets\n";
	exit(0); 
    }
    sleep 300;
}
