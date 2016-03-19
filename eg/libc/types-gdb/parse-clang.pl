#!/usr/bin/perl

# Usage:
# First, follow the directions in nm-to-c.pl. Then,
# % clang -Wno-deprecated-declarations -Xclang -ast-dump ptrs.c | perl parse-clang.pl >clang-types.out

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
    } elsif ($top =~ /\(void\)/) {
	$num_args = 0;
    } else {
	$num_args = $commas + 1;
    }
    printf "%4d %-2s %s %s\n", $i, $num_args, $name, $type;
}
