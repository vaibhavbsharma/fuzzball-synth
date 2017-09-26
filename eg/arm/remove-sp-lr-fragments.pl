#!/usr/bin/perl

use strict;

die "Usage: remove-sp-lr-fragments.pl <fragment directory to search> "
  unless @ARGV == 1;
my($dir) = @ARGV;

my @args = ("ls","$dir/");
open(FILES, "-|", @args);
while(<FILES>) {
    chomp $_;
    my $file = $_;
    # printf("$file\n");
    open(FILE,"<$dir/$file");
    my ($l0,$l1,$l2);
    while(<FILE>) {
	chomp $_;
	$l2=$l1;
	$l1=$l0;
	$l0=$_;
	# printf("$_\n");
    }
    # printf("\n\n l2 = $l2\n");
    if($l2 eq "0d 00 a0 e1" || $l2 eq "0e 00 a0 e1") {
	printf("deleting $dir/$file\n");
	`rm $dir/$file`;
    }
}
