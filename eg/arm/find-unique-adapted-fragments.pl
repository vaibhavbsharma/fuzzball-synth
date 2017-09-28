#!/usr/bin/perl

use strict;

die "Usage: find-unique-adaptors.pl <log-file-to-be-grepped-to-extract-unique-adaptors> <number of bucket directories> <directory where to look for arm-[1..bucket-number]>"  unless @ARGV == 3;
my($log_file_name,$num_dirs,$dir) = @ARGV;

my %adaptors_str = ();
for (my $dir_suffix = 1; $dir_suffix <= $num_dirs; $dir_suffix++) {
    my $file_name = $dir."/arm-".$dir_suffix."/logs/".$log_file_name;
    printf("grepping on $file_name\n");
    open(LOG, "<" . $file_name) or die "could not open $file_name";
    while(<LOG>) {
	if(/Final adaptor for .*\/.*\.frag is.*$/) {
      # printf("line = $_\n");
	    my @arr = split /\s+/, $_;
      # print "arr[3] = $arr[4]\n";
      my @s1 = split /\//, $arr[4];
	    my @s2 = split /_/, $s1[scalar(@s1)-1];
      # printf("s1 = @s1, s2 = @s2\n");
	    my $str = join(" ", @arr[5..$#arr]);
      # printf("arr = $str\n");
	    if(exists $adaptors_str{$s2[0]}) {
		push $adaptors_str{$s2[0]}, ($s2[1], $s1[scalar(@s1)-1], $s1[3], $str);
	    } else {
		$adaptors_str{$s2[0]} = [($s2[1], $s1[4], $s1[scalar(@s1)-1], $str)];
	    }
	}
    }
}

for my $key (keys %adaptors_str) {
    my @arr = @{$adaptors_str{$key}};
    for (my $i=0; $i < scalar(@arr); $i+=4) {
	my ($end_lno, $file_name, $fragment, $adaptor) = ($arr[$i], $arr[$i+1], $arr[$i+2], $arr[$i+3]);
	printf("$key mapped to $end_lno, $file_name, fragment = $dir/$fragment, adaptor = $adaptor\n");
    }
}
printf("unique starting lines = %d\n", scalar((keys %adaptors_str)));
