#!/usr/bin/perl

use strict;

die "Usage: keep-job-running.pl <.qsub file name> <dir at itasca where .qsub file is located>"
  unless @ARGV == 2;

my ($job_name,$dir) = @ARGV;

if( substr($job_name, length($job_name)-5) =~ ".qsub") {
    $job_name = substr($job_name, 0, length($job_name)-5);
}

while(1) {
    my $output = `ssh itasca "qstat -u vaibhav -f"`;
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection timed out") != -1) { printf("Connection closed!\n"); exit(1); }
    if(index($output, "Connection closed") != -1) { printf("Connection closed!\n"); exit(1); }
    my $found = 0;
    if(index($output, $job_name) != -1) { $found = 1; }
# printf("found = $found\n");
    if($found == 0) {
	my $output= `ssh itasca "qsub $dir/$job_name.qsub"`;
	printf("new job queued: output = $output\n");
    }
    sleep 60;
}