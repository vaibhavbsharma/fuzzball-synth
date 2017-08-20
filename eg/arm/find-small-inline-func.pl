#!/usr/bin/perl

use strict;

die "Usage: find-small-inline-func.pl <path-to-functions-list> <directory-prefix>"
  unless @ARGV == 2;
my ($lst_file,$dir_prefix) = @ARGV;

my @file_path;
open(F, "<", $lst_file) or die;
while (<F>) {
    my $file = $_;
    chomp $file;
    my $str = $dir_prefix . "/" . $file;
    push @file_path, $str;
}
close F;

my $function_body_flag = 0;
my $lines = 0;
my $function_name;
my $parens = 0;
my $THRESHOLD = 10;
my $func_body_str;
for my $file (@file_path) {
    open(FRAG_FILE, "<", $file) or die;
    while (<FRAG_FILE>) {
	if($function_body_flag == 1) {
	    $lines++;
	    $func_body_str .= $_;
	    if(/.*{.*/) { 
		$parens += 1; 
		# printf("p+$_");
	    }
	    elsif(/.*}.*/) { 
		$parens -= 1;
		# printf("p-$_");
		if($parens == 0) {
		    if($lines < $THRESHOLD) {
			printf("small inline function = $func_body_str\n");
		    } 
		    # else {
		    # 	printf("large inline function = $func_body_str\n-x-x-\n");
		    # }
		    $func_body_str="";
		    $function_body_flag = 0;
		    $lines = 0;
		}	       
	    }
	}
	if(/.*inline.*\(.*$/ || /.*INLINE.*\(.*$/) {
	    $lines = 0;
	    $parens = 0;
	    $function_name = $_;
	    $func_body_str = $_;
	    # print $_;
	    my $line = $_;
	    if(index($line, '}') == -1) {
		$function_body_flag = 1;
		if(index($line, '{') != -1) {
		    $parens += 1;
		}
	    } else { 
		$function_body_flag = 0; 
		printf("small inline function = $_\n");
	    }
	    
	}
    }
}
