#!/usr/bin/perl

use strict;


die "Usage: count-insns.pl <path-to-dump-file>"
  unless @ARGV == 1;
my ($dump_file) = @ARGV;

printf("dump_file = %s\n", $dump_file);
my $line_num = 1;

my $start_num = 64842;
my $end_num = 64846;


open(FRAG, ">f");
printf(FRAG "04 00 9b e5\n"); #   ldr     r0 [fp #4]\n");
printf(FRAG "08 10 9b e5\n"); #   ldr     r1 [fp #8]\n");
printf(FRAG "0c 20 9b e5\n"); #   ldr     r2 [fp #12]\n");
printf(FRAG "10 30 9b e5\n"); #   ldr     r3 [fp #16]\n");
printf(FRAG "14 40 9b e5\n"); #   ldr     r4 [fp #20]\n");
printf(FRAG "18 50 9b e5\n"); #   ldr     r5 [fp #24]\n");

my @recent_w_regs = ("null", "null", "null");
my $ind = 0;

open(F, "<$dump_file") or die;
while (<F>) {
    if($line_num >= $start_num && $line_num <= $end_num) {
	my $bytes="";
	my $insn_str="";
	if(/^ ([0-9a-f]+):  ([0-9a-f]+)  (.*)$/) {
	    # printf("address = $1, bytes = $2, ");
	    $bytes = $2; $insn_str = $3;
	    if(/^ ([0-9a-f]+):  ([0-9a-f]+)  (.*)  (.*), (.*)$/) {
		# printf("reg = $4\n");
		if ( !grep( /^$4$/, @recent_w_regs ) ) {
		    $recent_w_regs[$ind] = $4;
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
	printf(" $b4, $b3, $b2, $b1, // $insn_str\n");
	printf(FRAG "$b4 $b3 $b2 $b1\n");
	# print "$_";
    } 
    $line_num += 1;
}
printf("line_num = %d\n", $line_num);
my $ret_reg_byte = 0;
for my $str (@recent_w_regs) {
    if ($str =~ "r1") {
	printf(FRAG "01 00 a0 e1\n"); #   mov    r0 r1\n"); 
    }
    elsif ($str =~ "r2") {
	printf(FRAG "02 00 a0 e1\n"); #   mov    r0 r2\n"); 
    }
    elsif ($str =~ "r3") {
	printf(FRAG "03 00 a0 e1\n"); #   mov    r0 r3\n"); 
    }
    elsif ($str =~ "r4") {
	printf(FRAG "04 00 a0 e1\n"); #   mov    r0 r4\n"); 
    }
    elsif ($str =~ "r5") {
	printf(FRAG "05 00 a0 e1\n"); #   mov    r0 r5\n"); 
    }
    elsif ($str =~ "r6") {
	printf(FRAG "06 00 a0 e1\n"); #   mov    r0 r6\n"); 
    }
    elsif ($str =~ "r7") {
	printf(FRAG "07 00 a0 e1\n"); #   mov    r0 r7\n"); 
    }
    elsif ($str =~ "r8") {
	printf(FRAG "08 00 a0 e1\n"); #   mov    r0 r8\n"); 
    }
    elsif ($str =~ "r9") {
	printf(FRAG "09 00 a0 e1\n"); #   mov    r0 r9\n"); 
    }
    elsif ($str =~ "sl") {
	printf(FRAG "0a 00 a0 e1\n"); #   mov    r0 sl\n"); 
    }
    elsif ($str =~ "fp") {
	printf(FRAG "0b 00 a0 e1\n"); #   mov    r0 fp\n"); 
    }
    elsif ($str =~ "ip") {
	printf(FRAG "0c 00 a0 e1\n"); #   mov    r0 ip\n"); 
    }
    elsif ($str =~ "sp") {
	printf(FRAG "0d 00 a0 e1\n"); #   mov    r0 sp\n"); 
    }
    elsif ($str =~ "lr") {
	printf(FRAG "0e 00 a0 e1\n"); #   mov    r0 lr\n"); 
    }
    else {
	printf(FRAG "00 00 a0 e1\n"); #   nop\n");
    }
}
printf(FRAG "1e ff 2f e1\n"); #   bx     lr\n");
printf(FRAG "00 00 a0 e1\n"); #   nop\n");
close FRAG;

printf("recent_w_regs = @recent_w_regs\n");
