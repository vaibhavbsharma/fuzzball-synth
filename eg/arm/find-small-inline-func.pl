#!/usr/bin/perl

use strict;

die "Usage: find-small-inline-func.pl <path-to-files-list> <directory-prefix>"
  unless @ARGV == 2;
my ($lst_file,$dir_prefix) = @ARGV;

my @file_path;
open(F, "<", $lst_file) or die;
while (<F>) {
    my $file = $_;
    chomp $file;
    push @file_path, $file;
}
close F;

my $function_body_flag = 0;
my $lines = 0;
my $function_name;
my $parens = 0;
my $THRESHOLD = 20;
my $func_body_str;
my $func_count=0;
for my $file (@file_path) {
    # print "file = $file\n";
    $lines = 0;
    $parens = 0;
    my $void_args = 0;
    open(FRAG_FILE, "<", $file) or die;
    while (<FRAG_FILE>) {
	$lines++;
	# print "$parens $lines $_";
	if(/.*{.*/) { 
	    $parens += 1;
	    if($parens == 1) { 
		$lines = 1; 
		if(index($func_body_str,"(void)") != -1) {
		    $void_args = 1;
		}
	    }
	    # print "p+\n";
	}
	if($parens > 0) {
	    $func_body_str .= $_;
	}
	elsif ($parens == 0) { 
	    $func_body_str = $_;
	}
	if(/.*}.*/) { 
	    $parens -= 1;
	    # print "p-\n";
	    if($parens == 0) {
		if(index($func_body_str, "->") != -1 ||
		   index($func_body_str, "[") != -1 ||
		   index($func_body_str, "]") != -1 ||
		   index($func_body_str, "print") != -1 ||
		   index($func_body_str, "*") != -1 ||
		   index($func_body_str, ".") != -1 ||
		   index($file, "firmware/target/arm/archos") != -1 ||
		   index($file, "firmware/target/arm/as3525") != -1 ||
		   index($file, "firmware/target/arm/at91sam") != -1 ||
		   index($file, "firmware/target/arm/imx31") != -1 ||
		   index($file, "firmware/target/arm/imx233") != -1 ||
		   index($file, "firmware/target/arm/philips") != -1 ||
		   index($file, "firmware/target/arm/pbell") != -1 ||
		   index($file, "firmware/target/arm/olympus") != -1 ||
		   index($file, "firmware/target/arm/iriver") != -1 ||
		   index($file, "firmware/target/arm/rk27xx") != -1 ||
		   index($file, "firmware/target/arm/pp") != -1 ||
		   index($file, "firmware/target/arm/pnx0101") != -1 ||
		   index($file, "firmware/target/arm/s5l8700") != -1 ||
		   index($file, "firmware/target/arm/s3c2440") != -1 ||
		   index($file, "firmware/target/arm/tatung") != -1 ||
		   index($file, "firmware/target/arm/sandisk") != -1 ||
		   index($file, "firmware/target/arm/samsung") != -1 ||
		   index($file, "firmware/target/arm/s5l8702") != -1 ||
		   index($file, "firmware/target/arm/tcc780x") != -1 ||
		   index($file, "firmware/target/arm/tcc77x") != -1 ||
		   index($file, "firmware/target/arm/tms320dm320") != -1 ||
		   index($file, "firmware/target/mips") != -1 ||
		   index($file, "firmware/target/coldfire") != -1 ||
		   index($file, "firmware/target/sh") != -1 ||
		   index($file, "firmware/target/hosted") != -1 ||
		   index($file, "apps/plugins") != -1 ||
		    index($func_body_str, "return") == -1 ||
		    $void_args == 1) {
		    $lines = $THRESHOLD+1;
		}
		if($lines < $THRESHOLD) {
		    $func_count++;
		    print "small function in $file: $func_body_str\n";
		} 
		# else {
		# 	printf("large inline function = $func_body_str\n-x-x-\n");
		# }
		$func_body_str="";
		$lines = 0;
		$void_args = 0;
	    }
	}
    }
}

print "Total functions = $func_count";
