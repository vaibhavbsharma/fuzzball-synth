#!/usr/bin/perl

use strict;

sub by_length ($$) { length($_[0]) <=>  length($_[1]) }

my %name;

while (<>) {
    next unless /^([0-9a-f]{16}) (.) (\w+)$/;
    my($addr, $type, $name) = ($1, $2, $3);
    $addr = hex $addr;
    next unless $type =~ /^[TW]$/;
    $name{$addr}{$name} = 1;
}

print <<END;
#include <stdio.h>

typedef long (*func)(long, long, long, long, long, long);

func funcs[] = {
END

for my $a (sort keys %name) {
    my @names = sort keys %{$name{$a}};
    my $name;
    if (@names == 1) {
	$name = $names[0];
    } else {
	@names = sort by_length @names;
	my $shortest = $names[0];
	@names = grep($_ ne "__$shortest", @names);
	@names = grep($_ ne "__$shortest" . "64", @names);
	@names = grep($_ ne "__libc_$shortest", @names);
	@names = grep($_ ne "_IO_$shortest", @names);
	@names = grep($_ ne "_IO_$shortest" . "64", @names);
	@names = grep($_ ne $shortest . "64", @names);
	@names = grep($_ ne $shortest . "_unlocked", @names);
	if (@names == 1) {
	    $name = $shortest;
	} else {
	    #my $names = join(" ", @names);
	    #for my $n (@names) { 
	#	printf "%d,%s ", length($n), $n;
	    #}
	    #print "\n";
	    $name = $shortest;
	}
    }
    next if $name =~ /^__/;
    #printf "%08x $name\n", $a;
    print "    (func)$name,\n";
}

print <<END;
};

int main(int argc, char **argv) {
    (funcs[1])((long)"Hello, world!", 0, 0, 0, 0, 0);
    return 0;
}
END
