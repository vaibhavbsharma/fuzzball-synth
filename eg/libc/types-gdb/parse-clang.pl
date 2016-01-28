#!/usr/bin/perl

use strict;

my @names;

open(C, "<ptrs.c");
while (<C>) {
    next unless /^    \(func\)(\w+),$/;
    my $n = $1;
    push @names, $n;
    #printf "%4d %s\n", $#names, $n;
}

my %types;
while (<>) {
    next unless /FunctionDecl/;
    /\e\[0;1;36m (\w+?)\e\[0m.*\e\[0;32m'(.*?)'/
      or die;
    my($func, $type) = ($1, $2);
    $types{$func} = $type;
}

for my $i (0 .. $#names) {
    my $name = $names[$i];
    my $type = $types{$name};
    my $top = $type;
    $top =~ s/__attribute__\(\(noreturn\)\)//;
    while (($top =~ tr/(/(/) > 1) {
	$top =~ s/\([^()]*\)//;
    }
    my $commas = ($top =~ tr/,/,/);
    my $num_args;
    if ($top =~ /\.\.\./) {
	$num_args = "$commas+";
    } else {
	$num_args = $commas + 1;
    }
    printf "%4d %-2s %s %s %s\n", $i, $num_args, $name, $type;
}
