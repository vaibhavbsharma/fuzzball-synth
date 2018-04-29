#!/usr/bin/perl

my $misc_size = 0;
my %decl_size;
my %def_size;

while (<>) {
    if (/^\(assert \(= ([\w-]+) /) {
	my $var = $1;
	die "Missing decl. of $var" unless exists $decl_size{$var};
	die "Duplicate def. of $var" if exists $def_size{$var};
	$def_size{$var} = length($_);
    } elsif (/^\(declare-fun ([\w-]+) /) {
	my $var = $1;
	die "Duplicate decl. of $var" if exists $decl_size{$var};
	$decl_size{$var} = length($_);
    } else {
	$misc_size += length($_);
    }
}

my $total = 0;
for my $var (sort keys %decl_size) {
    my $decl_size = exists $decl_size{$var} ? $decl_size{$var} : 0;
    my $def_size = exists $def_size{$var} ? $def_size{$var} : 0;
    print "$var: $decl_size+$def_size\n";
    $total += $decl_size;
    $total += $def_size;
}
$total += $misc_size;

print "Total: $total\n";

