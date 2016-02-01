#!/usr/bin/perl

use strict;

my $i = 0;

while (<>) {
    my($num, $nargs, $name, $type) = split(" ", $_, 4);
    my $nargs_plain = 0 + $nargs;
    my $is_vararg = ($nargs =~ /\+/) ? "1" : "0";
    printf qq[    /* %4d */ {"$name", (func*)&$name, $nargs_plain, $is_vararg},\n],
      $i;
    $i++;
}
