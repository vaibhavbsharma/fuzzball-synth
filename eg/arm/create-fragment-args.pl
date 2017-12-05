#!/usr/bin/perl

use strict;

die "Usage: create-fragments.pl <path-to-dump-file> <fragment file directory> <fragment file>"
  unless @ARGV == 3;
my ($dump_file,$file_prefix,$frag_file_input) = @ARGV;

my $debug = 0;

my $frag_file = $frag_file_input;
if(index($frag_file_input, "/") != -1) {
    $frag_file = substr($frag_file_input, rindex($frag_file_input, "/") + 1);
}

my $pos1 = index($frag_file, "_");
my $pos2 = index($frag_file, "_", $pos1 + 1);
if($pos1 == -1 || $pos2 == -1) {
    print "error: failed to find position of \"_\" in fragment file\n";
    exit(1);
}

# my $start_num = 64859; #64872; #64842;
# my $end_num = 64863; #64876; #64846;
my $start_num = substr($frag_file, 0, $pos1);
my $end_num = substr($frag_file, $pos1 + 1, $pos2 - $pos1 - 1);

if($debug) { print "start = $start_num, end = $end_num\n"; }

my @w_regs = ();
my @frag_args = ();
my $reg_number = -1;
my $ind = 0;
open(F, "<$dump_file") or die;
my $line_num = 1;
while (<F>) {
    if(($line_num >= $start_num) && ($line_num <= $end_num)) {
	chomp $_;
	if($debug) { print "$line_num| $_, "; }
	my $bytes="";
	my $insn_str="";
	my $mnemonic;
	if(/^ *([0-9a-f]+):  ([0-9a-f]+)   (.*)$/) {
	    if($debug) { printf("address = $1, bytes = $2, "); }
	    $bytes = $2; $insn_str = $3;
	    $mnemonic = substr($insn_str, 0, index($insn_str, ' '));
	    if(index($insn_str, ';') != -1) {
		$insn_str = substr($insn_str, 0, index($insn_str, ';'));
	    }
	    my $write_reg="";
	    if($debug) { printf("insn_str = $insn_str, "); }
	    my $comma_pos;
	    if(index($insn_str, ',') != -1) {
		$comma_pos = index($insn_str, ',');
		my $space_pos = $comma_pos;
		while(substr($insn_str, $space_pos, 1) ne " ") {
		    $space_pos--;
		}
		if($debug) { printf("comma_pos = $comma_pos, space_pos = $space_pos, "); }
		$write_reg = substr($insn_str, $space_pos+1, $comma_pos-$space_pos-1); 
	    }
	    
	    if($mnemonic =~ /cmp/ && is_reg($write_reg)) { 
		my $read_reg = $reg_number;
		$write_reg = "";
		if( !grep( /^$read_reg$/, @frag_args ) ) {
		    push @frag_args, $reg_number;
		    if($debug) { print "read_reg = $read_reg, "; }
		}
		$insn_str = "";
	    }
	    while(index($insn_str, ',') != -1) {
		$insn_str = substr($insn_str, $comma_pos + 1);
		if($debug) { print "\ninsn_str = $insn_str, "; }
		my $next_comma_pos = index($insn_str, ',');
		my $read_reg;
		if($next_comma_pos != -1) {
		    $read_reg = substr($insn_str, 1, $next_comma_pos-1);
		} else { $read_reg = substr($insn_str, 1); }
		$comma_pos = $next_comma_pos;
		if(is_reg($read_reg) && # is_reg initializes reg_number
		   !grep( /^$reg_number$/, @w_regs ) && 
		   !grep( /^$reg_number$/, @frag_args )) {
		    push @frag_args, $reg_number;
		    if($debug) { print "read_reg = $read_reg, "; }
		}
	    }
	    if($write_reg ne "" && !( $write_reg =~ /sp/) && !($write_reg =~ /lr/) &&
		!($mnemonic =~ /cmp/) ) {
		if($debug) { printf("reg = $write_reg, "); }
		if ( is_reg($write_reg) &&
		     !grep( /^$reg_number$/, @w_regs ) ) {
		    $w_regs[$ind] = $reg_number;
		    $ind = $ind + 1;
		}
	    }
	}
	if($debug) { print "\n"; }
	(length $bytes) == 8 || die "ARM32 instructions cannot be more than 8 bytes long";
    }
    $line_num += 1;
}
printf("line_num = %d\n", $line_num);
printf("w_regs = @w_regs\n");
printf("frag_args = @frag_args\n");

my $file_name = $frag_file_input . ".args";
if($debug) { printf("file_name = $file_name\n"); }
open(FRAG, ">", $file_name);
foreach (@frag_args) { print FRAG "$_\n"; }
close FRAG;
printf("Wrote to $file_name\n");


sub is_reg {
    my $reg = shift(@_);
    my $ret = 0;
    if ($reg =~ /r0/) {
	$ret = 1;
	$reg_number = 0;
    } elsif ($reg =~ /r1/) {
	$ret = 1;
	$reg_number = 1;
    } elsif ($reg =~ /r2/) {
	$ret = 1;
	$reg_number = 2;
    } elsif ($reg =~ /r3/) {
	$ret = 1;
	$reg_number = 3;
    } elsif ($reg =~ /r4/) {
	$ret = 1;
	$reg_number = 4;
    } elsif ($reg =~ /r5/) {
	$ret = 1;
	$reg_number = 5;
    } elsif ($reg =~ /r6/) {
	$ret = 1;
	$reg_number = 6;
    } elsif ($reg =~ /r7/) {
	$ret = 1;
	$reg_number = 7;
    } elsif ($reg =~ /r8/) {
	$ret = 1;
	$reg_number = 8;
    } elsif ($reg =~ /r9/) {
	$ret = 1;
	$reg_number = 9;
    } elsif ($reg =~ /sl/ && index($reg, "sl") == 0) {
	$ret = 1;
	$reg_number = 10;
    } elsif ($reg =~ /fp/) {
	$ret = 1;
	$reg_number = 11;
    } elsif ($reg =~ /ip/) {
	$ret = 1; 
	$reg_number = 12;
    }
    # elsif ($reg =~ /sp/) {
    # 	$ret = 0;
    # } elsif ($reg =~ /lr/) {
    # 	$ret = 0;
    # }
    return $ret;
}
