#!/usr/bin/perl

use strict;

die "Usage: run-fragments.pl <fragments-dir> <bucket-num(1-16)>"
  unless @ARGV == 2;
my ($fragments_dir,$bucket_num) = @ARGV;

my $rand_seed = 1;
my $const_lb = 0;
my $const_ub = 255;

my @fragments = `ls $fragments_dir | grep -i .frag`;
printf("# of frags = %d\n", scalar(@fragments));

my $bucket_size = scalar(@fragments)/16;
my $starting_frag = ($bucket_num-1)*$bucket_size;
my $ending_frag = $starting_frag + $bucket_size;

for(my $i = $starting_frag; $i < $ending_frag; $i++) {
    my $frag_file = $fragments[$i];
    $frag_file =~ s/\n//;
    $frag_file = $fragments_dir . "/" . $frag_file;
    my @cmd = ("perl","synth-test1.pl","1","2",$rand_seed, "1", $const_lb, $const_ub,
	       "1", "$frag_file");
    printf("cmd = @cmd\n");
    open(LOG, "-|", @cmd);
    while(<LOG>) {
	print $_;
    }
}
