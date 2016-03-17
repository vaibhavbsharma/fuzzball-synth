#!/usr/bin/perl

# Usage of this script:
# % cp headers.h ptrs.c
# % nm -D libc.so | perl nm-to-c.pl >>ptrs.c
# % gcc -Wno-deprecated-declarations ptrs.c -o ptrs

use strict;

sub by_length ($$) { length($_[0]) <=>  length($_[1]) }

my %name;

while (<>) {
    next unless /^([0-9a-f]{16}) (.) (\w+)$/;
    my($addr, $type, $name) = ($1, $2, $3);
    $addr = hex $addr;
    next unless $type =~ /^[TWi]$/;
    $name{$addr}{$name} = 1;
}

my @blacklist =
  ("chflags", "fchflags", # only stubs
   "sigvec", # not in 2.21
  );
my %blacklist;
@blacklist{@blacklist} = (1) x @blacklist;

print <<END;
typedef long (*func)(long, long, long, long, long, long);

func funcs[] = {
END

my %seen;

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
    next if $name =~ /^_IO_/;
    next if $name =~ /^_dl_/;
    next if $name =~ /^_nss_/;
    next if $name =~ /^_obstack_/;
    next if $blacklist{$name};
    next if $seen{$name};
    $seen{$name} = 1;
    #printf "%08x $name\n", $a;
    print "    (func)$name,\n";
}

print <<END;
};

int main(int argc, char **argv) {
    long args[6] = {0, 0, 0, 0, 0, 0};
    int i;
    int fn_num;
    if (argc < 2 || argc > 7) {
	fprintf(stderr, "Usage: ptrs fnnum [0-6 args]\\n");
	exit(1);
    }
    fn_num = atoi(argv[1]);
    for (i = 0; i < 6 && i + 2 < argc; i++) {
	char *s = argv[i + 2];
	if (isdigit(s[0])) {
	    args[i] = atol(s);
	} else {
	    args[i] = (long)s;
	}
    }
    (funcs[fn_num])(args[0], args[1], args[2], args[3], args[4], args[5]);
    /*(funcs[862])((long)"Hello, world!", 0, 0, 0, 0, 0);*/
    return 0;
}
END
