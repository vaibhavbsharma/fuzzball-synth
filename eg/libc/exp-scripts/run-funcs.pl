#!/usr/bin/perl
use POSIX;
use strict;
use File::Basename;

die "Usage: run-funcs.pl <max_buckets> <bucket-num(1-max_buckets)> <1=argsub, 2=typeconv adaptor, 3=arithmetic-depth-2-adapter> <constant lower bound> <constant upper bound>"
  unless @ARGV == 5;


$|=1;
my $end_time = time() + 2592000; # keep running for up to 30 days
my $checkpoint_file = "checkpoint";

my ($max_buckets,$bucket_num,$adaptor_family,$const_lb,$const_ub) = @ARGV;

my $rand_seed = 1;
my $num_secs_to_timeout = 300;
if ($adapter_family == 3) { $num_secs_to_timeout = 600; } # arithmetic adapter gets 10m timeout
my $num_glibc_fns = 1316;
my $binary = "two-funcs";

# if($adaptor_family == 1) { $num_secs_to_timeout = 60; }
# else { $num_secs_to_timeout = 300; }# https://stackoverflow.com/questions/1962985/how-can-i-timeout-a-forked-process-that-might-hang

open(LOG, ">> logs/run-funcs.log");
printf(LOG "# of funcs = %d\n", $num_glibc_fns);
select((select(LOG), $|=1)[0]);
printf("# of funcs = %d\n", $num_glibc_fns);

my $bucket_size = ceil($num_glibc_fns/$max_buckets);
my $starting_target_fn = ($bucket_num-1)*$bucket_size;
my $ending_target_fn = $starting_target_fn + $bucket_size;
if($ending_target_fn > $num_glibc_fns) { $ending_target_fn = $num_glibc_fns-1; }
my $this_bucket_num_fns = $ending_target_fn-$starting_target_fn+1;
print "bucket_size = $bucket_size\n";
print "starting_target_fn = $starting_target_fn\n";
print "ending_target_fn = $ending_target_fn\n";
my $last_index = -1;
open (FILE, "< $checkpoint_file");
while (<FILE>) {
  $last_index = $_ + 0;
}
close FILE;

print LOG "last index = $last_index\n";
select((select(LOG), $|=1)[0]);
print "last index = $last_index\n";
if ( $last_index+1 >= $this_bucket_num_fns) {
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

for(my $i = $last_index+1; $i < $this_bucket_num_fns; $i++) {
    my $target_fn = $starting_target_fn + $i;
    my $inner_func_start = $target_fn-5;
    if ($inner_func_start < 0 ) { $inner_func_start = 0; }
    my $inner_func_end = $target_fn+5;
    if ($inner_func_end >= $num_glibc_fns) { $inner_func_end = $num_glibc_fns-1; }
    for (my $inner_fn = $inner_func_start; 
	 $inner_fn <= $inner_func_end; 
	 $inner_fn++) {
	if ($target_fn == $inner_fn) { next; }
	my $adaptor_driver = "synth-argsub.pl";
	if($adaptor_family==2) { $adaptor_driver = "synth-typeconv.pl"; }
	elsif($adaptor_family==3) { $adaptor_driver = "synth-arithmetic.ml"; }
	my @cmd = ("perl",$adaptor_driver,$target_fn,$inner_fn,$rand_seed, "1", 
		   $const_lb, $const_ub, "0", "0");
	if ($adaptor_family == 3) {
	    @cmd = ("./synth-arithmetic", $binary,"int","2",$target_fn, $inner_fn, $rand_seed,"0", "2>&1");
	}
	printf(LOG "cmd = @cmd\n");
	select((select(LOG), $|=1)[0]);
	printf("cmd = @cmd\n");
	print STDERR "cmd = @cmd\n";
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
		if($timed_out == 1) { last; }
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
		print " $_" unless (/.*Query time = .*/ || /.*Starting new query.*$/);
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
}
