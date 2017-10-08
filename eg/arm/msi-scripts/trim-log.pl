#!/usr/bin/perl

use strict;

die "Usage: trim-log.pl <log file name> <number of \"identity-fragments\" to skip> <number of directories> <base dir. absolute path>"
  unless @ARGV == 4;
my($log_file_name,$skip_num, $num_dirs,$dir_path) = @ARGV;

for(my $i=1; $i <= $num_dirs; $i++) {
    my $count = 0;
    my $trim_done = 0;
    open(LOG,"<$dir_path/arm-$i/logs/$log_file_name");
    open(TRIM_LOG,">$dir_path/arm-$i/logs/$log_file_name.trimmed");
    while(<LOG>) {
	if(/.*identity-fragments = .*/) { $count++; }
	if($count == $skip_num) { $trim_done = 1; }
	if($trim_done == 1) {
	   print TRIM_LOG $_; 
	}
    }
  print "Wrote to $dir_path/arm-$i/logs/$log_file_name.trimmed\n";
    close LOG;
    close TRIM_LOG;
}
