#!/usr/bin/perl

use strict;

die "Usage: post-process-adapters.pl <adapter family, typeconv=2, arithmetic=3> <refK-arithmetic-adapters.lst file>\n" .
    "use this perl script to convert the adapters reported by report-arith-adapters.sh from a list form to a header file containing a C structure of all the argret/arithd2ret adapters\n"
    unless @ARGV==2;
my ($family, $file) = @ARGV;
if ($family < 2 || $family > 3) {
    die "unsupported adapter family";
}
open(F, "<$file") or die;
my $num_adapters = 0;
my $adapters = "";
while (<F>) {
    chomp $_;
    my $line = $_;
    $line =~ s/\(/{/g;
    $line =~ s/\)/}/g;
    $line =~ s/and \{/, /g;
    if ($family == 3) { $line =~ s/,$/}}, /g; }
    else { $line =~ s/$/, /g; }
    $line = '{' . $line . "\n";
    $adapters = $adapters . $line;
    $num_adapters++;
}
close F;

my $prefix = "#include \"adapter_types.h\"\n";
$prefix = $prefix . "int num_adapters = $num_adapters;\n";
if ($family == 3) {
    $prefix = $prefix . "arithd2ret";
} else { $prefix = $prefix . "argret"; }
$prefix = $prefix . " all_ads[$num_adapters] = {\n";

my $suffix = "};";

my $final_output= $prefix . $adapters . $suffix;
print $final_output;


