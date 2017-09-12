#!/usr/bin/perl

use strict;

die "Usage: find-unique-adaptors.pl <log-file-to-be-grepped-to-extract-unique-adaptors>"
  unless @ARGV == 1;
my($log_file_name) = @ARGV;

my %adaptors_str = ();
for (my $dir_suffix = 1; $dir_suffix <= 16; $dir_suffix++) {
    my $file_name = "../arm-".$dir_suffix."/logs/".$log_file_name;
    printf("grepping on $file_name\n");
    open(LOG, "<" . $file_name) or die "could not open $file_name";
    while(<LOG>) {
	if(/Final adaptor for \.\.\/arm\/fragments6\/\/.*\.frag is.*/) {
	    # printf("line = $_\n");
	    my @arr = split /\s+/, $_;
	    my @s1 = split /\//, $arr[3];
	    my @s2 = split /_/, $s1[4];
	    if(exists $adaptors_str{$s2[0]}) {
		push $adaptors_str{$s2[0]}, ($s2[1], $s1[4]);
	    } else {
		$adaptors_str{$s2[0]} = [($s2[1],$s1[4])];
	    }
	}
    }
}

printf("unique starting lines = %d\n", scalar((keys %adaptors_str)));

for my $key (keys %adaptors_str) {
    my @arr = @{$adaptors_str{$key}};
    for (my $i=0; $i < scalar(@arr); $i+=2) {
	my ($end_lno, $file_name) = ($arr[$i], $arr[$i+1]);
	printf("$key mapped to $end_lno, $file_name\n");
    }
}
