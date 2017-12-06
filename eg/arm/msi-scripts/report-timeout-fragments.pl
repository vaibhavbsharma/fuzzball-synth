#!/usr/bin/perl

use strict;

die "Usage: report-timeout-fragments.pl <log file name> <number of bucket directories> <base dir. absolute paths file>"
  unless @ARGV == 3;
my($log_file_name,$num_dirs,$dir_paths_file) = @ARGV;
my @timed_out_frags = ();
sub report_metrics {
    my $dir_path = shift(@_);
    my $log_file_name = shift(@_);
    my $num_dirs = shift(@_);
    my $total_results = 0;
    my $total_cmds = 0;
    my @tmp_arr = split /\//, $dir_path;
    my $fn_name = $tmp_arr[$#tmp_arr];
    my $saved_frag;
    print "Starting analysis for $fn_name\n";
    for(my $i=1; $i <= $num_dirs; $i++) {
	open(LOG,"<$dir_path/arm-$i/logs/$log_file_name");
	my $saved_cmd = "";
	while(<LOG>) {
	    if(/.*cmd =.*/) {
		$total_cmds++;
		chomp $_;
		my @tmp_arr = split / /, $_;
		$saved_frag = $tmp_arr[$#tmp_arr-2];
	    }
	    if(/^found timeout$/) { 
		$total_results++; 
		push @timed_out_frags, $saved_frag;
	    }
	} # end while(<LOG>)
    }
}

open(FILES, "<$dir_paths_file");
while(<FILES>) {
    chomp $_;
    report_metrics($_, $log_file_name, $num_dirs);
}
foreach(@timed_out_frags) { print "$_\n"; }
