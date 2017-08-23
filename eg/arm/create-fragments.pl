#!/usr/bin/perl

use strict;


die "Usage: create-fragments.pl <path-to-dump-file> <fragment-prefix> <starting-line-num> <ending-line-num>"
  unless @ARGV == 4;
my ($dump_file,$file_prefix,$start_num,$end_num) = @ARGV;

# printf("dump_file = %s\n", $dump_file);
my $line_num = 1;

# my $start_num = 64859; #64872; #64842;
# my $end_num = 64863; #64876; #64846;


my $frag_contents;
$frag_contents .= sprintf("04 00 9b e5\n"); #   ldr     r0 [fp #4]\n");
$frag_contents .= sprintf("08 10 9b e5\n"); #   ldr     r1 [fp #8]\n");
$frag_contents .= sprintf("0c 20 9b e5\n"); #   ldr     r2 [fp #12]\n");
$frag_contents .= sprintf("10 30 9b e5\n"); #   ldr     r3 [fp #16]\n");
$frag_contents .= sprintf("14 40 9b e5\n"); #   ldr     r4 [fp #20]\n");
$frag_contents .= sprintf("18 50 9b e5\n"); #   ldr     r5 [fp #24]\n");

my @recent_w_regs = ("null", "null", "null");
my $ind = 0;

open(F, "<$dump_file") or die;
while (<F>) {
    if(($line_num >= $start_num) && ($line_num <= $end_num)) {
	# print("line = $_, ($line_num)");
	my $bytes="";
	my $insn_str="";
	if(/^ ([0-9a-f]+):  ([0-9a-f]+)   (.*)$/) {
	    # printf("address = $1, bytes = $2, ");
	    $bytes = $2; $insn_str = $3;
	    if(/^ ([0-9a-f]+):  ([0-9a-f]+)  (.*)  (.*)$/) {
		my $cmd = $4;
		if(index($cmd, ',') == -1) { $line_num += 1; next; }
		my $write_reg = substr $cmd, 0, index($cmd, ',');
		# printf("reg = $write_reg\n");
		if ( !grep( /^$write_reg$/, @recent_w_regs ) ) {
		    $recent_w_regs[$ind] = $write_reg;
		    $ind = ($ind + 1) % 3;
		}
	    } else { #printf("\n"); 
	    }
	}
	(length $bytes) == 8 || die "ARM32 instructions cannot be more than 8 bytes long";
	my $b1 = substr $bytes, 0, 2;
	my $b2 = substr $bytes, 2, 2;
	my $b3 = substr $bytes, 4, 2;
	my $b4 = substr $bytes, 6, 2;
	# printf(" $b4, $b3, $b2, $b1, // $insn_str\n");
	$frag_contents .= sprintf("$b4 $b3 $b2 $b1\n");
	# print "$_";
    } 
    $line_num += 1;
}
# printf("line_num = %d\n", $line_num);
my $file_num = 1;
my $ret_reg_byte = 0;
for my $str (@recent_w_regs) {
    my $added_ret_reg = 1;
    my $ret_insn = "";
    if ($str =~ "r0") {
	$ret_insn = sprintf("00 00 a0 e1\n"); #   nop\n");
	$added_ret_reg = 1;
    } elsif ($str =~ "r1") {
	$ret_insn = sprintf("01 00 a0 e1\n"); #   mov    r0 r1\n"); 
    } elsif ($str =~ "r2") {
	$ret_insn = sprintf("02 00 a0 e1\n"); #   mov    r0 r2\n"); 
    } elsif ($str =~ "r3") {
	$ret_insn = sprintf("03 00 a0 e1\n"); #   mov    r0 r3\n"); 
    } elsif ($str =~ "r4") {
	$ret_insn = sprintf("04 00 a0 e1\n"); #   mov    r0 r4\n"); 
    } elsif ($str =~ "r5") {
	$ret_insn = sprintf("05 00 a0 e1\n"); #   mov    r0 r5\n"); 
    } elsif ($str =~ "r6") {
	$ret_insn = sprintf("06 00 a0 e1\n"); #   mov    r0 r6\n"); 
    } elsif ($str =~ "r7") {
	$ret_insn = sprintf("07 00 a0 e1\n"); #   mov    r0 r7\n"); 
    } elsif ($str =~ "r8") {
	$ret_insn = sprintf("08 00 a0 e1\n"); #   mov    r0 r8\n"); 
    } elsif ($str =~ "r9") {
	$ret_insn = sprintf("09 00 a0 e1\n"); #   mov    r0 r9\n"); 
    } elsif ($str =~ "sl") {
	$ret_insn = sprintf("0a 00 a0 e1\n"); #   mov    r0 sl\n"); 
    } elsif ($str =~ "fp") {
	$ret_insn = sprintf("0b 00 a0 e1\n"); #   mov    r0 fp\n"); 
    } elsif ($str =~ "ip") {
	$ret_insn = sprintf("0c 00 a0 e1\n"); #   mov    r0 ip\n"); 
    } elsif ($str =~ "sp") {
	$ret_insn = sprintf("0d 00 a0 e1\n"); #   mov    r0 sp\n"); 
    } elsif ($str =~ "lr") {
	$ret_insn = sprintf("0e 00 a0 e1\n"); #   mov    r0 lr\n"); 
    } else {
	$ret_insn = sprintf("00 00 a0 e1\n"); #   nop\n");
	$added_ret_reg = 0;
    }
    if($added_ret_reg == 1) {
	my $file_name = $file_prefix . $start_num . "_" . $end_num . "_" . $file_num . ".frag";
	$file_num += 1;
	open(FRAG, ">", $file_name);
	printf(FRAG $frag_contents);
	printf(FRAG $ret_insn);
	printf(FRAG "1e ff 2f e1\n"); #   bx     lr\n");
	printf(FRAG "00 00 a0 e1\n"); #   nop\n");
	close FRAG;
	printf("Wrote to $file_name\n");
    }
}

# printf("recent_w_regs = @recent_w_regs\n");
