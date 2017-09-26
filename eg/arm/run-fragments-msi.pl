#!/usr/bin/perl

use strict;

die "Usage: run-fragments.pl <fragments-dir> <max_buckets> <bucket-num(1-max_buckets)> <min-fragment-length> <max-fragment-length> <1=find identity fragments, any other value=avoid identity fragments using <fragments-dir>/identity-fragments.lst> <1=argsub, 2=typeconv adaptor> <constant bounds file>"
  unless @ARGV == 8;

my $this_fragments_file = "this_fragments.lst";
my $checkpoint_file = "checkpoint";

my ($fragments_dir,$max_buckets,$bucket_num,$min_frag_size,$max_frag_size,$find_identity_frag,$adaptor_family,$const_bounds_file) = @ARGV;

my $rand_seed = 1;
my $num_secs_to_timeout;
if($adaptor_family == 1) { $num_secs_to_timeout = 60; }
else { $num_secs_to_timeout = 120; }# https://stackoverflow.com/questions/1962985/how-can-i-timeout-a-forked-process-that-might-hang

my @identity_fragments = ();
if($find_identity_frag != 1) {
    open(F, $fragments_dir . "/identity-fragments.lst") or die;
    while (<F>) {
	my $line = $_;
	push @identity_fragments, substr($line, 0, length($line)-1);
    }
    printf("#identity-fragments = %d\n", scalar(@identity_fragments));
} else { printf("finding identity fragments\n"); } 

sub is_identity_fragment  {
    if($find_identity_frag == 1) { return 0; }
    my $frag_file = shift(@_);
    foreach my $file (@identity_fragments) {
	# printf("identity-fragment-file = $file\n");
	if(index($frag_file, $file) != -1) {
	    printf("skipping $frag_file because $file is identity\n");
	    return 1;
	}
    }
    return 0;
}

my @this_bucket_fragments = ();
my $open_failed = 0;
open(FH, "<$this_fragments_file") || do { $open_failed = 1; };
if($open_failed == 0) {
  @this_bucket_fragments = <FH>;
  close FH;
} else {
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
  
  my $bucket_size = scalar(@filtered_fragments)/$max_buckets;
  my $starting_frag = ($bucket_num-1)*$bucket_size;
  my $ending_frag = $starting_frag + $bucket_size;
  if($ending_frag > scalar(@filtered_fragments)) { $ending_frag = scalar(@filtered_fragments)-1; }
  @filtered_fragments = sort {$a->[1] <=> $b->[1]} @filtered_fragments;
  
  # for(my $i=0;$i < scalar(@filtered_fragments); $i++) {
  #     printf("($i) frag_file = %s\n", $filtered_fragments[$i][0]);
  # } 
  
  for(my $i = $bucket_num-1; $i < scalar(@filtered_fragments); $i += $max_buckets) {
     push @this_bucket_fragments, $filtered_fragments[$i][0]; #, $filtered_fragments[$i][1]]; 
  }
  
  open (FILE, ">> $this_fragments_file") || die "problem opening $this_fragments_file\n";
  for(my $i = 0; $i < scalar(@this_bucket_fragments); $i++) {
    printf(FILE "%s\n", $this_bucket_fragments[$i]);
  }
  close FILE;
}
my $last_index = -1;
open (FILE, "< $checkpoint_file");
while (<FILE>) {
  $last_index = $_ + 0;
  print "last index = $last_index\n";
}


for(my $i = $last_index+1; $i < scalar(@this_bucket_fragments); $i++) {
    my $frag_file = $this_bucket_fragments[$i];
    if(($find_identity_frag != 1) && 
       (is_identity_fragment($frag_file) == 1)) { next; }
    # my $distance = $this_bucket_fragments[$i][1];
    $frag_file =~ s/\n//;
    # printf("frag_file = $frag_file, distance = $distance\n");
    $frag_file = $fragments_dir . "/" . $frag_file;
    
    my $inner_func_num = 0;
    if($find_identity_frag == 1) { $inner_func_num = 3; } 
    else { $inner_func_num = 2; }

    my $adaptor_driver = "synth-argsub-frag.pl";
    if($adaptor_family==2) { $adaptor_driver = "synth-typeconv-frag.pl"; }
    
    my @cmd = ("perl",$adaptor_driver,"1",$inner_func_num,$rand_seed, "1", $const_bounds_file,
	       "1", "$frag_file", "0");
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
    open (FILE, ">> $checkpoint_file") || die "problem opening checkpoint file: $checkpoint_file\n";
    print FILE $i . "\n";
    close FILE;
}
