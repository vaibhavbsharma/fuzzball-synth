#!/usr/bin/perl

my @names;

open(C, "<ptrs.c");
while (<C>) {
    next unless /^    \(func\)(\w+),$/;
    my $n = $1;
    push @names, $n;
    #printf "%4d %s\n", $#names, $n;
}

open(G, ">gdb-cmds.gdb");
print G "b 1734\nrun\ns\nq\n";
close G;

for my $num (0 .. $#names) {
    my $name = $names[$num];
    open(GO, "gdb --args ./ptrs $num <gdb-cmds.gdb 2>/dev/null |");
    scalar <GO> for 1 .. 20;
    my $line;
#     while (<GO>) {
# 	$line = $_;
# 	print "X $line";
#     }
    $line = <GO>;
    next unless $line =~ /^\(gdb\) (\w+) /;
    my $name2 = $1;
    printf "%4d %s %s ", $num, $name, $name2;
    while (<GO>) {
	#print $_;
    }
    #sleep 1;
    close GO;
    open(G2, ">gdb-cmds.gdb");
    print G2 "b 1734\nrun\ns\nptype $name2\nq\n";
    close G2;
    open(GO2, "gdb --args ./ptrs $num <gdb-cmds.gdb 2>/dev/null|");
    while (<GO2>) {
	$line = $_;
	if ($line =~ /^\(gdb\) type = (.*)/) {
	    my $type = $1;
	    print "$type ";
	    last;
	}
    }
    while (<GO2>) {
	last if /A debugging session is active/;
	s/^\s+//; s/\s+$//;
	print " $_ ";
    }
    print "\n";
    while (<GO2>) { }
    close GO2;
}
