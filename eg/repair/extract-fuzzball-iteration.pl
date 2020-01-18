#!/usr/bin/perl

use strict;

die "Usage: extract-fuzzball-iteration.pl <log-file-generated-from-FuzzBALL> <iteration-number to be extracted>"
  unless @ARGV == 2;
my($log_file,$it_num) = @ARGV;


open (FILE, $log_file);
my $trace_log = 0;
while (<FILE>) {
    if (/^.*Iteration ([0-9]+):$/) {
	my $it = $1;
	if ($it_num == $it) { $trace_log = 1; }
	else { $trace_log = 0; }
    }
    if ($trace_log == 1) { print $_; } 
}
close FILE;
