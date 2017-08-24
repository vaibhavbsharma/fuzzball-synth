#!/usr/bin/perl

use strict;

die "Usage: run-fragments.pl <fragments-dir> <bucket-num(1-16)> <min-fragment-length> <max-fragment-length>"
  unless @ARGV == 4;
my ($fragments_dir,$bucket_num,$min_frag_size,$max_frag_size) = @ARGV;

my $rand_seed = 1;
my $const_lb = 0;
my $const_ub = 255;
my $num_secs_to_timeout=15; # https://stackoverflow.com/questions/1962985/how-can-i-timeout-a-forked-process-that-might-hang

my @fragments = `ls $fragments_dir | grep -i .frag | sort `;
my @filtered_fragments = ();
for(my $i = 0; $i < scalar(@fragments); $i++) {
    my $frag_file = $fragments[$i];
    $frag_file =~ s/\n//;
    my @parts = split('_', $frag_file);
    # $parts[2] = substr($parts[2], 0, rindex($parts[2],'.'));
    if(($parts[1] - $parts[0] >= $min_frag_size) && 
       ($parts[1] - $parts[0] <= $max_frag_size)) {
	# printf("frag_file = $frag_file, parts[0] = $parts[0], parts[1] = $parts[1], parts[2] = $parts[2]\n");
	push @filtered_fragments, [$frag_file, $parts[2]];
    }
}
printf("# of frags = %d\n", scalar(@filtered_fragments));

my $bucket_size = scalar(@filtered_fragments)/16;
my $starting_frag = ($bucket_num-1)*$bucket_size;
my $ending_frag = $starting_frag + $bucket_size;
if($ending_frag > scalar(@filtered_fragments)) { $ending_frag = scalar(@filtered_fragments)-1; }
@filtered_fragments = sort {$a->[1] <=> $b->[1]} @filtered_fragments;

# for(my $i=0;$i < scalar(@filtered_fragments); $i++) {
#     printf("($i) frag_file = %s\n", $filtered_fragments[$i][0]);
# } 

my @this_bucket_fragments = ();
for(my $i = $bucket_num-1; $i < scalar(@filtered_fragments); $i += 16) {
   push @this_bucket_fragments, [$filtered_fragments[$i][0], $filtered_fragments[$i][1]]; 
}

for(my $i = 0; $i < scalar(@this_bucket_fragments); $i++) {
    my $frag_file = $this_bucket_fragments[$i][0];
    my $distance = $this_bucket_fragments[$i][1];
    $frag_file =~ s/\n//;
    # printf("frag_file = $frag_file, distance = $distance\n");
    $frag_file = $fragments_dir . "/" . $frag_file;
    my @cmd = ("perl","synth-test1.pl","1","2",$rand_seed, "1", $const_lb, $const_ub,
	       "1", "$frag_file");
    printf("cmd = @cmd\n");
    # open(LOG, "-|", @cmd);
    # while(<LOG>) {
    # 	print $_;
    # }
    my $retval;
    my $pid = fork;
    if ($pid > 0){ # parent process
    	eval{
    	    local $SIG{ALRM} = 
    		sub {kill 9, -$pid; print STDOUT "TIME OUT!$/"; $retval = 124;};
    	    alarm $num_secs_to_timeout;
    	    waitpid($pid, 0);
    	    alarm 0;
    	};
    }
    elsif ($pid == 0){ # child process
    	setpgrp(0,0);
    	exec(@cmd);
    } else { # forking not successful
    }
}
