#!/usr/bin/perl

use strict;

die "Usage: run-fragments.pl <fragments-dir> <bucket-num(1-16)> <min-fragment-length> <max-fragment-length>"
  unless @ARGV == 4;
my ($fragments_dir,$bucket_num,$min_frag_size,$max_frag_size) = @ARGV;

my $rand_seed = 1;
my $const_lb = 0;
my $const_ub = 255;

my @fragments = `ls $fragments_dir | grep -i .frag | sort `;
my @filtered_fragments = ();
for(my $i = 0; $i < scalar(@fragments); $i++) {
    my $frag_file = $fragments[$i];
    $frag_file =~ s/\n//;
    my @parts = split('_', $frag_file);
    if(($parts[1] - $parts[0] >= $min_frag_size) && 
       ($parts[1] - $parts[0] <= $max_frag_size)) {
	# printf("frag_file = $frag_file, parts[0] = $parts[0], parts[1] = $parts[1]\n");
	push @filtered_fragments, $frag_file;
    }
}
printf("# of frags = %d\n", scalar(@filtered_fragments));

my $bucket_size = scalar(@filtered_fragments)/16;
my $starting_frag = ($bucket_num-1)*$bucket_size;
my $ending_frag = $starting_frag + $bucket_size;

for(my $i = $starting_frag; $i < $ending_frag; $i++) {
    my $frag_file = $filtered_fragments[$i];
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
