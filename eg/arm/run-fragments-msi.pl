#!/usr/bin/perl

use strict;

die "Usage: run-fragments.pl <fragments-dir> <max_buckets> <bucket-num(1-max_buckets)> <min-fragment-length> <max-fragment-length> <1=find identity fragments, 2=boost_clamp,3-14=vlc ref. fns.> <1=argsub, 2=typeconv adaptor> <constant bounds file> <return => ret.val.sub.>"
  unless @ARGV == 9;

$|=1;
my $end_time = time() + 14400;
my $this_fragments_file = "this_fragments.lst";
my $checkpoint_file = "checkpoint";

my ($fragments_dir,$max_buckets,$bucket_num,$min_frag_size,$max_frag_size,$find_identity_frag,$adaptor_family,$const_bounds_file,$is_return_enabled) = @ARGV;

my $rand_seed = 1;
my $num_secs_to_timeout = 300;
# if($adaptor_family == 1) { $num_secs_to_timeout = 60; }
# else { $num_secs_to_timeout = 300; }# https://stackoverflow.com/questions/1962985/how-can-i-timeout-a-forked-process-that-might-hang

open(LOG, ">> logs/run-fragments-msi.log");
my @identity_fragments = ();
if($find_identity_frag != 1) {
    open(F, $fragments_dir . "/identity-fragments.lst") or die;
    while (<F>) {
	my $line = $_;
	push @identity_fragments, substr($line, 0, length($line)-1);
    }
    printf(LOG "#identity-fragments = %d\n", scalar(@identity_fragments));
    select((select(LOG), $|=1)[0]);
    printf("#identity-fragments = %d\n", scalar(@identity_fragments));
} else { 
    printf(LOG "finding identity fragments\n"); 
    select((select(LOG), $|=1)[0]);
    printf("finding identity fragments\n"); 
} 

sub is_identity_fragment  {
    if($find_identity_frag == 1) { return 0; }
    my $frag_file = shift(@_);
    foreach my $file (@identity_fragments) {
	# printf("identity-fragment-file = $file\n");
	if(index($frag_file, $file) != -1) {
	    printf(LOG "skipping $frag_file because $file is identity\n");
	    select((select(LOG), $|=1)[0]);
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
  printf(LOG "# of frags = %d\n", scalar(@filtered_fragments));
  select((select(LOG), $|=1)[0]);
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
  # print "last index = $last_index\n";
}
close FILE;

print LOG "last index = $last_index\n";
select((select(LOG), $|=1)[0]);
print "last index = $last_index\n";
if ( $last_index+1 >= scalar(@this_bucket_fragments)) {
	`touch done$bucket_num`;
	close LOG;
	exit(0);
}
my ($running_as) = (0,0);
my ($last_ce_time,$last_as_time) = (0,0);
my ($total_ce_time,$total_as_time,$total_time) = (0,0,0);
my ($total_as_steps,$total_ce_steps,$total_steps) = (0,0,0);
my ($total_as_solver_time,$last_as_solver_time) = (0.0,0.0);
my ($total_ce_solver_time,$last_ce_solver_time) = (0.0,0.0);
my ($saved_last_ce_solver_time,$saved_last_as_solver_time) = (0.0,0.0);
my $total_solver_time = 0.0;
my ($result) = (0);
my $timed_out = 0;
my $start_query_time = 0;
sub report_time_stats {
    my $stopping_step="";
    my $extra_stopping_str="";
    my $stopping_str = "";
    my $query_time=0;
    #printf("timed_out = $timed_out, start_query_time = $start_query_time, diff = %d\n",
    #time() - $start_query_time);
    if($timed_out == 1 && $start_query_time != 0) {
	if($running_as == 1) { 
	    $last_as_solver_time += time() - $start_query_time; 
	}
	else { 
	    $last_ce_solver_time += time() - $start_query_time; 
	}
    }
    if($timed_out == 1) {
	if($running_as == 1) { 
	    $total_as_steps++;
	    $total_as_solver_time += $last_as_solver_time;
	}
	else { 
	    $total_ce_steps++;
	    $total_ce_solver_time += $last_ce_solver_time;
	}
    }
    if($running_as == 1) { 
	$stopping_step = "Adaptor-Search"; 
	$query_time = $last_as_solver_time;
	$extra_stopping_str = "stopped during $stopping_step with solver time = $query_time\n";
    }
    else { 
	$stopping_step = "CounterExample-Search"; 
	$query_time = $last_ce_solver_time;
	$extra_stopping_str = "stopped during $stopping_step with solver time = $query_time\n";
    }
    if($result == 0) {
	$stopping_str = "found timeout\n";
    } elsif($result == 1) {
	$stopping_str = "found an adaptor\n";
    } elsif($result == 2) {
	$stopping_str = "found inequivalence\n";
    } elsif($result == 3) {
	$stopping_str = "found fatal error\n";
    } elsif($result == 4) {
	$stopping_str = "found ce failure\n";
    }
    if($last_as_solver_time == 0) { $last_as_solver_time = $saved_last_as_solver_time; }
    if($last_ce_solver_time == 0) { $last_ce_solver_time = $saved_last_ce_solver_time; }
    print LOG $stopping_str;
    printf(LOG "time (ce-total,ce-last,as-total,as-last,ce-as-total) = (%d,%d,%d,%d,%d)\n",
	   $total_ce_time,$last_ce_time,
	   $total_as_time,$last_as_time,
	   $total_as_time + $total_ce_time);
    printf(LOG "total steps (ce,as,total) = ($total_ce_steps,$total_as_steps,%d)\n",
	   $total_ce_steps + $total_as_steps);
    printf(LOG "solver times (ce-total,ce-last,as-total,as-last) = (%f,%f,%f,%f)\n",
	   $total_ce_solver_time,$last_ce_solver_time,
	   $total_as_solver_time,$last_as_solver_time);
    print LOG $extra_stopping_str;
    select((select(LOG), $|=1)[0]);

    print $stopping_str;
    printf("time (ce-total,ce-last,as-total,as-last,ce-as-total) = (%d,%d,%d,%d,%d)\n",
	   $total_ce_time,$last_ce_time,
	   $total_as_time,$last_as_time,
	   $total_as_time + $total_ce_time);
    printf("total steps (ce,as,total) = ($total_ce_steps,$total_as_steps,%d)\n",
	   $total_ce_steps + $total_as_steps);
    printf("solver times (ce-total,ce-last,as-total,as-last) = (%f,%f,%f,%f)\n",
	   $total_ce_solver_time,$last_ce_solver_time,
	   $total_as_solver_time,$last_as_solver_time);
    print $extra_stopping_str;
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
    else { $inner_func_num = $find_identity_frag; }

    my $adaptor_driver = "synth-argsub-frag.pl";
    if($adaptor_family==2) { $adaptor_driver = "synth-typeconv-frag.pl"; }
    
    my @cmd = ("perl",$adaptor_driver,"1",$inner_func_num,$rand_seed, "1", $const_bounds_file,
	       "1", "$frag_file", $is_return_enabled, "0");
    printf(LOG "cmd = @cmd\n");
    select((select(LOG), $|=1)[0]);
    printf("cmd = @cmd\n");
    # open(LOG, "-|", @cmd);
    # while(<LOG>) {
    # 	print $_;
    # }
    $running_as = 0;
    $last_ce_time = $last_as_time = 0;
    $total_ce_time = $total_as_time = $total_time = 0;
    $total_as_steps = $total_ce_steps = $total_steps = 0;
    $total_as_solver_time = $last_as_solver_time = 0.0;
    $total_ce_solver_time = $last_ce_solver_time = 0.0;
    $saved_last_as_solver_time = $saved_last_ce_solver_time = 0.0;
    $total_solver_time = 0.0;
    $result = 0;
    $timed_out = 0;
    my $pid = open(CHILD, "-|", @cmd);
    eval{
    	local $SIG{ALRM} = 
    	    sub {
    		kill 9, -$pid; 
    		print LOG "TIME OUT!$/";
    		print STDOUT "TIME OUT!$/";
    		$timed_out = 1;
    		report_time_stats ();
    	};
    	alarm $num_secs_to_timeout;
    	while(<CHILD>) {
    	    if($timed_out == 1) { 
    		# printf("timing out!!\n");
    		last;
    	    }
    	    if(/^elapsed time = (.*), last CE search time = (.*)$/) {
    		# printf("seen last CE\n");
    		$running_as = 1;
    		$last_ce_time = $2;
    		$total_ce_time += $2;
    		$total_time = $1;
    		$total_ce_steps++;
    		$total_ce_solver_time += $last_ce_solver_time;
		print LOG "last_as_solver_time = $last_as_solver_time\n";
		select((select(LOG), $|=1)[0]);
		$saved_last_as_solver_time = $last_as_solver_time;
		$last_as_solver_time = 0; #since we're about to start a new A.S. step
		$start_query_time = 0;
    	    } elsif(/^elapsed time = (.*), last AS search time = (.*)$/) {
    		# printf("seen last AS\n");
    		$running_as = 0;
    		$last_as_time = $2;
    		$total_as_time += $2;
    		$total_time = $1;
    		$total_as_steps++;
    		$total_as_solver_time += $last_as_solver_time;
		print LOG "last_ce_solver_time = $last_ce_solver_time\n";
		select((select(LOG), $|=1)[0]);
		$saved_last_ce_solver_time = $last_ce_solver_time;
		$last_ce_solver_time = 0; #since we're about to start a new C.E. step
		$start_query_time = 0;
    	    } elsif(/.*total query time = (.*)$/) {
    		# printf("seen Query time\n");
    		if($running_as == 1) { 
    		    $last_as_solver_time = $1 + 0;
    		} else { 
    		    $last_ce_solver_time = $1 + 0;
    		}
		$start_query_time = 0;
    	    } elsif(/.*Query time = (.*) sec$/) {
    		# printf("seen Query time\n");
    		if($running_as == 1) { 
    		    $last_as_solver_time += $1 + 0;
    		} else { 
    		    $last_ce_solver_time += $1 + 0;
    		}
		$start_query_time = 0;
    	    } elsif(/.*Starting new query.*$/) {
		$start_query_time = time();
	    } elsif(/.*Final adaptor.*/ && ($result == 0)) {
    		$result = 1;
    	    } elsif(/.*not equivalent.*/ && ($result == 0)) {
    		$result = 2;
    	    } elsif(/.*Fatal error.*/ && ($result == 0)) {
    		$result = 3;
    	    } elsif(/.*CounterExample search failed.*/ && ($result == 0)) {
    		$result = 4;
    	    }
    	    print " $_"; # unless (/.*Query time = .*/ || /.*Starting new query.*$/);
    	}
    	close(CHILD);
    	waitpid($pid, 0);
    	if($timed_out != 1) { report_time_stats (); }
    };
    open (FILE, ">> $checkpoint_file") || die "problem opening checkpoint file: $checkpoint_file\n";
    print FILE $i . "\n";
    close FILE;
    my $diff = $end_time - time();
    if($diff <= $num_secs_to_timeout) { 
	print LOG "exiting before timing out\n";
	select((select(LOG), $|=1)[0]);
	print "exiting before timing out\n";
	close LOG;
	exit(0); 
    }
    # exit(1);
}
