#!/usr/bin/perl

use strict;

die "Usage: report-metrics.pl <log file name> <number of bucket directories> <base dir. absolute paths file>"
  unless @ARGV >= 3;
my($log_file_name,$num_dirs,$dir_paths_file) = @ARGV;
my $log_file_name = $ARGV[0];
my $num_dirs = $ARGV[1];
my $dir_path = $ARGV[2];
my ($adaptor_steps_f, $adaptor_times_f, $timeout_steps_f) = (0,0,0);
my $argnum;
foreach $argnum (0 .. $#ARGV) {
    # print "$ARGV[$argnum]\n";
    if($ARGV[$argnum] eq "-adaptor-times") { $adaptor_times_f = 1; }
    if($ARGV[$argnum] eq "-adaptor-steps") { $adaptor_steps_f = 1; }
    if($ARGV[$argnum] eq "-timeout-steps") { $timeout_steps_f = 1; }
}
my $timeout_table .= "timeout:\n";
$timeout_table .= "fn_name, #, steps, total time (solver), CE total time (solver), CE last time (solver), AS total time (solver), AS last time (solver), AS-stops/CE-stops\n";
my $inequiv_table .= "inequiv:\n";
$inequiv_table .= "fn_name, #, steps, total time (solver), CE total time (solver), CE last time (solver), AS total time (solver), AS last time (solver)\n";
my $adaptor_table .= "adaptor:\n";
$adaptor_table .= "fn_name, #, steps, total time (solver), CE total time (solver), CE last time (solver), AS total time (solver), AS last time (solver)\n";

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

sub calc_count {
    my @arr = @{$_[0]};
    my $val1 = $_[1];
    my $val2 = $_[2];
    my ($count1,$count2) = (0,0);
	  for(my $i = 0; $i < scalar(@arr); $i++) {
      if($val1 == $arr[$i]) { $count1++; }
      if($val2 == $arr[$i]) { $count2++; }
    }
    return ($count1,$count2);
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
    } else { return (0,0,0,0); }
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
    } else { return (0,0,0,0,0); }
}

my %seen_cmds = ();

sub report_metrics {
    @timeout_time = ();
    @timeout_steps = ();
    @timeout_solver = ();
    @timeout_stopped_during = ();

    @adaptor_time = ();
    @adaptor_steps = ();
    @adaptor_solver = ();

    @inequiv_time = ();
    @inequiv_steps = ();
    @inequiv_solver = ();

    @fatal_time = ();
    @fatal_steps = ();
    @fatal_solver = ();

    @ce_fail_time = ();
    @ce_fail_steps = ();
    @ce_fail_solver = ();

    my $dir_path = shift(@_);
    my $log_file_name = shift(@_);
    my $num_dirs = shift(@_);
    my $total_results = 0;
    my $total_cmds = 0;
    my @tmp_arr = split /\//, $dir_path;
    my $fn_name = $tmp_arr[$#tmp_arr];
    if(index($fn_name, "ref3") != -1) { $fn_name = "bswap32(#1)"; }
    if(index($fn_name, "ref4") != -1) { $fn_name = "integer_cmp(#2)"; }
    if(index($fn_name, "ref5") != -1) { $fn_name = "even(#1)"; }
    if(index($fn_name, "ref6") != -1) { $fn_name = "div255(#1)"; }
    if(index($fn_name, "ref7") != -1) { $fn_name = "reverse_bits(#1)"; }
    if(index($fn_name, "ref8") != -1) { $fn_name = "binary_log(#1)"; }
    if(index($fn_name, "ref9") != -1) { $fn_name = "fixmul32(#2)"; }
    if(index($fn_name, "ref10") != -1 &&
       index($fn_name, "ref10-") == -1) { $fn_name = "median(#3)"; }
    if(index($fn_name, "ref11") != -1) { $fn_name = "hex_value(#1)"; }
    if(index($fn_name, "ref12") != -1) { $fn_name = "transform_from_basic_ops(#10)"; }
    if(index($fn_name, "ref13") != -1) { $fn_name = "get_descriptor_length_24b(#1)"; }
    if(index($fn_name, "ref14") != -1) { $fn_name = "tile_pos(#4)"; }
    if(index($fn_name, "ref15") != -1) { $fn_name = "diract_picture_n_before_m(#2)"; }
    if(index($fn_name, "ref16") != -1) { $fn_name = "ps_id_to_tk(#1)"; }
    if(index($fn_name, "ref17") != -1) { $fn_name = "leading_zero_count(#1)"; }
    if(index($fn_name, "ref18") != -1) { $fn_name = "trailing_zero_count(#1)"; }
    if(index($fn_name, "ref19") != -1) { $fn_name = "popcnt_32(#1)"; }
    if(index($fn_name, "ref20") != -1) { $fn_name = "parity(#1)"; }
    if(index($fn_name, "ref21") != -1) { $fn_name = "dv_audio_12_to_16(#1)"; }
    if(index($fn_name, "ref22") != -1) { $fn_name = "is_power_2(#1)"; }
    if(index($fn_name, "ref23") != -1) { $fn_name = "RenderRGB(#3)"; }
    if(index($fn_name, "ref24") != -1) { $fn_name = "decode_BCD(#1)"; }
    if(index($fn_name, "ref25") != -1) { $fn_name = "mpga_get_frame_samples(#1)"; }
    if(index($fn_name, "ref1") != -1
       && index($fn_name, "ref10-") == -1) { $fn_name = "prev_pow_2(#1)"; }
    if(index($fn_name, "ref2") != -1) { $fn_name = "abs_diff(#2)"; }
    my $total_runtime = 300;
    if(index($dir_path, "2.5m") != -1) {
	$total_runtime = 150;
    } elsif(index($dir_path, "10m") != -1) {
	$total_runtime = 600;
    } elsif(index($dir_path, "20m") != -1) {
	$total_runtime = 1200;
    }elsif(index($dir_path, "40m") != -1) {
	$total_runtime = 2400;
    }

    print "Starting analysis for $fn_name\n";

    for(my $i=1; $i <= $num_dirs; $i++) {
	open(LOG,"<$dir_path/arm-$i/logs/$log_file_name");
	my ($result,$count) = (-1,0);
	my $saved_cmd = "";
	my ($line_num) = (0);
	my @saved_result_str = ();
	while(<LOG>) {
	    if(/.*cmd =.*/) {
		@saved_result_str = (); $count = 0; $result = -1;
		$total_cmds++; $saved_cmd = $_; chomp $saved_cmd;
		if(scalar(@timeout_time)/5 != scalar(@timeout_solver)/5 ||
		   scalar(@timeout_solver)/5 != scalar(@timeout_steps)/3 ||
		   scalar(@inequiv_time)/5 != scalar(@inequiv_solver)/5 ||
		   scalar(@inequiv_solver)/5 != scalar(@inequiv_steps)/3 ||
		   scalar(@adaptor_time)/5 != scalar(@adaptor_solver)/5 ||
		   scalar(@adaptor_solver)/5 != scalar(@adaptor_steps)/3) {
		    die sprintf("file($dir_path/arm-$i/logs/$log_file_name), line($line_num), number of timeouts or inequiv or adaptor instances dont match between time, solver, or steps" . 
				"(%.1f,%.1f,%.1f), (%.1f,%.1f,%.1f), (%.1f,%.1f,%.1f)\n", 
				scalar(@timeout_time)/5, scalar(@timeout_solver)/5, scalar(@timeout_steps)/3,
				scalar(@inequiv_time)/5, scalar(@inequiv_solver)/5, scalar(@inequiv_steps)/3,
			    scalar(@adaptor_time)/5, scalar(@adaptor_solver)/5, scalar(@adaptor_steps)/3);
		}
	    }
	    if(/^found timeout$/) { $total_results++; $result = 0; $line_num++; next; }
	    if(/^found an adaptor$/) { $total_results++; $result = 1; $line_num++; next; }
	    if(/^found inequivalence$/) { $total_results++; $result = 2; $line_num++; next; }
	    if(/.*found fatal error.*/) { $total_results++; $result = 3; $line_num++; next; }
	    if(/.*found ce failure.*/) { $total_results++; $result = 4; $line_num++; next; }
	    if($result != -1 && /^cmd = .*$/) {
		$result = -1;
		$count = 0;
	    }
	    if($result >= 0 && $result <= 4 && $count < 4) {
		$count++;
		chomp $_;
		push @saved_result_str, $_;
		if(/^#identity-fragments = .*$/) {
		    @saved_result_str = ();
		}
	    }
	    if($result >= 0 && $result <= 4 && $count == 4 && scalar(@saved_result_str) == 4) {
		if (!exists($seen_cmds{$saved_cmd})) {
		    $seen_cmds{$saved_cmd} = 1;
		    for(my $i = 0; $i < 4; $i++) {
			my $str = $saved_result_str[$i];
			if($str =~ /^time \(ce-total,ce-last,as-total,as-last,ce-as-total\) = \((.*),(.*),(.*),(.*),(.*)\)$/ ) {
			    # print "time string: $str\n";
			    my ($v1,$v2,$v3,$v4,$v5) = ($1,$2,$3,$4,$5);
			    for($result) {
				/0/ && do { push @timeout_time, ($v1,$v2,$v3,$v4,$v5); last; };
				/1/ && do { push @adaptor_time, ($v1,$v2,$v3,$v4,$v5); last; };
				/2/ && do { push @inequiv_time, ($v1,$v2,$v3,$v4,$v5); last; };
				/3/ && do { push @fatal_time,   ($v1,$v2,$v3,$v4,$v5); last; };
				/4/ && do { push @ce_fail_time, ($v1,$v2,$v3,$v4,$v5); last; };
			    }
			} elsif($str =~ /^total steps \(ce,as,total\) = \((.*),(.*),(.*)\)$/) {
			    # print "steps string: $str\n";
			    my ($v1,$v2,$v3) = ($1,$2,$3);
			    for($result) {
				/0/ && do { push @timeout_steps, ($v1,$v2,$v3); last; };
				/1/ && do { push @adaptor_steps, ($v1,$v2,$v3); last; };
				/2/ && do { push @inequiv_steps, ($v1,$v2,$v3); last; };
				/3/ && do { push @fatal_steps,   ($v1,$v2,$v3); last; };
				/4/ && do { push @ce_fail_steps, ($v1,$v2,$v3); last; };
			    }
			} elsif($str =~ /^solver times \(ce-total,ce-last,as-total,as-last\) = \((.*),(.*),(.*),(.*)\)$/) {
			    # print "solver string: $str\n";
			    my ($v1,$v2,$v3,$v4) = ($1,$2,$3,$4);
			    for($result) {
				/0/ && do { push @timeout_solver, ($v1,$v2,$v3,$v4,$v1+$v3); last; };
				/1/ && do { push @adaptor_solver, ($v1,$v2,$v3,$v4,$v1+$v3); last; };
				/2/ && do { push @inequiv_solver, ($v1,$v2,$v3,$v4,$v1+$v3); last; };
				/3/ && do { push @fatal_solver,   ($v1,$v2,$v3,$v4,$v1+$v3); last; };
				/4/ && do { push @ce_fail_solver, ($v1,$v2,$v3,$v4,$v1+$v3); last; };
			    }
			} elsif($str =~ /^stopped during (.*) with solver time = (.*)$/ && $result == 0) {
			    # print "stopped-during string: $str\n";
			    if($1 =~ "Adaptor-Search") {
				push @timeout_stopped_during, 1;
				if($result == 0) {
				    #$timeout_steps[scalar(@timeout_steps)-2]++;
				    #$timeout_steps[scalar(@timeout_steps)-1]++;
				    #$timeout_solver[scalar(@timeout_solver)-3]+=$2;
				    my $last_run_time = 
					($total_runtime - $timeout_time[scalar(@timeout_time)-1]); 
				    $timeout_time[scalar(@timeout_time)-2]=
					$last_run_time;
				    $timeout_time[scalar(@timeout_time)-3]+=
					$last_run_time;
				    $timeout_time[scalar(@timeout_time)-1] = $total_runtime;
				}
			    } elsif($1 =~ "CounterExample-Search") {
				push @timeout_stopped_during, 2;
				if($result == 0) {
				    #$timeout_steps[scalar(@timeout_steps)-3]++;
				    #$timeout_steps[scalar(@timeout_steps)-1]++;
				    #$timeout_solver[scalar(@timeout_solver)-5]+=$2; 
				    my $last_run_time = 
					($total_runtime - $timeout_time[scalar(@timeout_time)-1]); 
				    $timeout_time[scalar(@timeout_time)-4]=
					$last_run_time;
				    $timeout_time[scalar(@timeout_time)-5]+=
					$last_run_time;
				    $timeout_time[scalar(@timeout_time)-1] = $total_runtime;
				}
			    }
			}
		    }
		    $result = -1;
		    @saved_result_str = ();
		} # end if !exists($seen_cmds{$saved_cmd})
	    } # end if result >= 0 && <= 4
	    $line_num++;
	} # end while(<LOG>)
    }

    print "total cmds = $total_cmds, total results = $total_results\n";
    print "steps: (timeout,adaptor,inequiv,fatal,ce_fail)\n";
    my ($t_st_ce,$t_st_as,$t_st_t) = calc_average_3(\@timeout_steps);
    printf("$t_st_ce, $t_st_as, $t_st_t, %d\n",scalar(@timeout_steps)/3);
    my ($a_st_ce,$a_st_as,$a_st_t) = calc_average_3(\@adaptor_steps);
    printf("$a_st_ce, $a_st_as, $a_st_t, %d\n", scalar(@adaptor_steps)/3);
    my ($i_st_ce,$i_st_as,$i_st_t) = calc_average_3(\@inequiv_steps);
    printf("$i_st_ce, $i_st_as, $i_st_t, %d\n", scalar(@inequiv_steps)/3);
    my ($f_st_ce,$f_st_as,$f_st_t) = calc_average_3(\@fatal_steps);
    printf("$f_st_ce, $f_st_as, $f_st_t, %d\n", scalar(@fatal_steps)/3);
    my ($cef_st_ce,$cef_st_as,$cef_st_t) = calc_average_3(\@ce_fail_steps);
    printf("$cef_st_ce, $cef_st_as, $cef_st_t, %d\n", scalar(@ce_fail_steps)/3);
    print "\n";

    print "solver: (timeout,adaptor,inequiv,fatal,ce_fail)\n";
    my ($t_so_ce_t,$t_so_ce_l, $t_so_as_t,$t_so_as_l,$t_so_t) = calc_average_5(\@timeout_solver);
    printf("$t_so_ce_t, $t_so_ce_l, $t_so_as_t, $t_so_as_l, %d\n", scalar(@timeout_solver)/5);
    my ($a_so_ce_t,$a_so_ce_l,$a_so_as_t,$a_so_as_l,$a_so_t) = calc_average_5(\@adaptor_solver);
    printf("$a_so_ce_t, $a_so_ce_l, $a_so_as_t, $a_so_as_l, %d\n", scalar(@adaptor_solver)/5);
    my ($i_so_ce_t,$i_so_ce_l,$i_so_as_t,$i_so_as_l,$i_so_t) = calc_average_5(\@inequiv_solver);
    printf("$i_so_ce_t, $i_so_ce_l, $i_so_as_t, $i_so_as_l, %d\n", scalar(@inequiv_solver)/5);
    my ($f_so_ce_t,$f_so_ce_l,$f_so_as_t,$f_so_as_l,$f_so_t) = calc_average_5(\@fatal_solver);
    printf("$f_so_ce_t, $f_so_ce_l, $f_so_as_t, $f_so_as_l, %d\n", scalar(@fatal_solver)/5);
    my ($cef_so_ce_t,$cef_so_ce_l,$cef_so_as_t,$cef_so_as_l,$cef_so_t) = calc_average_5(\@ce_fail_solver);
    printf("$cef_so_ce_t, $cef_so_ce_l, $cef_so_as_t, $cef_so_as_l, %d\n", scalar(@ce_fail_solver)/5);
    print "\n";

    print "time: (timeout,adaptor,inequiv,fatal,ce_fail)\n";
    my ($t_tm_ce_t, $t_tm_ce_l,$t_tm_as_t, $t_tm_as_l,$t_tm_t) = calc_average_5(\@timeout_time);
    printf("$t_tm_ce_t, $t_tm_ce_l, $t_tm_as_t, $t_tm_as_l, $t_tm_t, %d\n", scalar(@timeout_time)/5);
    my ($a_tm_ce_t, $a_tm_ce_l,$a_tm_as_t, $a_tm_as_l,$a_tm_t) = calc_average_5(\@adaptor_time);
    printf("$a_tm_ce_t, $a_tm_ce_l, $a_tm_as_t, $a_tm_as_l, $a_tm_t, %d\n", scalar(@adaptor_time)/5);
    my ($i_tm_ce_t, $i_tm_ce_l,$i_tm_as_t, $i_tm_as_l,$i_tm_t) = calc_average_5(\@inequiv_time);
    printf("$i_tm_ce_t, $i_tm_ce_l, $i_tm_as_t, $i_tm_as_l, $i_tm_t, %d\n", scalar(@inequiv_time)/5);
    my ($f_tm_ce_t, $f_tm_ce_l,$f_tm_as_t, $f_tm_as_l,$f_tm_t) = calc_average_5(\@fatal_time);
    printf("$f_tm_ce_t, $f_tm_ce_l, $f_tm_as_t, $f_tm_as_l, $f_tm_t, %d\n", scalar(@fatal_time)/5);
    my ($cef_tm_ce_t, $cef_tm_ce_l,$cef_tm_as_t, $cef_tm_as_l,$cef_tm_t) = calc_average_5(\@ce_fail_time);
    printf("$cef_tm_ce_t, $cef_tm_ce_l, $cef_tm_as_t, $cef_tm_as_l, $cef_tm_t, %d\n", scalar(@ce_fail_time)/5);

    if(scalar(@timeout_time)/5 != scalar(@timeout_solver)/5 ||
       scalar(@timeout_solver)/5 != scalar(@timeout_steps)/3 ||
       scalar(@inequiv_time)/5 != scalar(@inequiv_solver)/5 ||
       scalar(@inequiv_solver)/5 != scalar(@inequiv_steps)/3 ||
       scalar(@adaptor_time)/5 != scalar(@adaptor_solver)/5 ||
       scalar(@adaptor_solver)/5 != scalar(@adaptor_steps)/3) {
	die sprintf("number of timeouts or inequiv or adaptor instances dont match between time, solver, or steps" . 
	     "(%.1f,%.1f,%.1f), (%.1f,%.1f,%.1f), (%.1f,%.1f,%.1f)\n", 
	     scalar(@timeout_time)/5, scalar(@timeout_solver)/5, scalar(@timeout_steps)/3,
	     scalar(@inequiv_time)/5, scalar(@inequiv_solver)/5, scalar(@inequiv_steps)/3,
	     scalar(@adaptor_time)/5, scalar(@adaptor_solver)/5, scalar(@adaptor_steps)/3);
    }
    
    my ($as_count,$ce_count) = calc_count(\@timeout_stopped_during,1,2);
    # printf("Average# timeout stopped during = AS(%d), CE(%d)\n\n", $as_count,$ce_count);
    $timeout_table .= 
	sprintf("$fn_name, %d, %.1f, %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), $as_count/$ce_count\n",
		scalar(@timeout_time)/5,
		$t_st_t, $t_tm_t, $t_so_t, 
		$t_tm_ce_t, $t_so_ce_t, 
		$t_tm_ce_l ,$t_so_ce_l, 
		$t_tm_as_t ,$t_so_as_t, 
		$t_tm_as_l ,$t_so_as_l);

    $inequiv_table .= 
	sprintf("$fn_name, %d, %.1f, %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f)\n", 
		scalar(@inequiv_time)/5,
		$i_st_t, $i_tm_t, $i_so_t, 
		$i_tm_ce_t, $i_so_ce_t, 
		$i_tm_ce_l ,$i_so_ce_l, 
		$i_tm_as_t ,$i_so_as_t, 
		$i_tm_as_l ,$i_so_as_l);


    $adaptor_table .= 
	sprintf("$fn_name, %d, %.1f, %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f), %.1f (%.1f)\n", 
		scalar(@adaptor_time)/5,
		$a_st_t, $a_tm_t, $a_so_t, 
		$a_tm_ce_t, $a_so_ce_t, 
		$a_tm_ce_l ,$a_so_ce_l, 
		$a_tm_as_t ,$a_so_as_t, 
		$a_tm_as_l ,$a_so_as_l);



    if($adaptor_times_f == 1) {
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
    }
    if($adaptor_steps_f == 1) {
	print "Adaptor steps:\n";
	my @arr = @adaptor_steps;
	for(my $i=0; $i < scalar(@arr); $i+=3) {
	    my $val1 = $arr[$i];
	    my $val2 = $arr[$i+1];
	    my $val3 = $arr[$i+2];
	    print "$val3\n";
	}
    }
    if($adaptor_steps_f == 1) {
	print "Timeout steps:\n";
	my @arr = @timeout_steps;
	for(my $i=0; $i < scalar(@arr); $i+=3) {
	    my $val1 = $arr[$i];
	    my $val2 = $arr[$i+1];
	    my $val3 = $arr[$i+2];
	    print "$val3\n";
	}
    }
}

open(FILES, "<$dir_paths_file");
while(<FILES>) {
    chomp $_;
    report_metrics($_, $log_file_name, $num_dirs);
}
print "$timeout_table\n";
print "$inequiv_table\n";
print "$adaptor_table\n";
