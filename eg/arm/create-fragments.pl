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
$frag_contents .= sprintf("1c 60 9b e5\n"); #   ldr	r6, [fp, #28]
$frag_contents .= sprintf("20 70 9b e5\n"); #   ldr	r7, [fp, #32]
$frag_contents .= sprintf("24 80 9b e5\n"); #   ldr	r8, [fp, #36]	; 0x24
$frag_contents .= sprintf("28 90 9b e5\n"); #   ldr	r9, [fp, #40]	; 0x28
$frag_contents .= sprintf("2c a0 9b e5\n"); #   ldr	sl, [fp, #44]	; 0x2c

my @recent_w_regs = ("null", "null", "null");
my $ind = 0;

open(F, "<$dump_file") or die;
while (<F>) {
    if(($line_num >= $start_num) && ($line_num <= $end_num)) {
	# print("$line_num| $_");
	my $bytes="";
	my $insn_str="";
	if(/^ ([0-9a-f]+):  ([0-9a-f]+)   (.*)$/) {
	    # printf("address = $1, bytes = $2, ");
	    $bytes = $2; $insn_str = $3;
	    my $mnemonic = substr($insn_str, 0, index($insn_str, ' '));
	    my $bucket = get_bucket($mnemonic);
	    # printf(" mnemonic($mnemonic) has bucket($bucket)\n");
	    if(index($insn_str, ';') != -1) {
		$insn_str = substr($insn_str, 0, index($insn_str, ';'));
	    }
	    my $write_reg="";
	    # printf("insn_str = $insn_str, ");
	    if(index($insn_str, ',') != -1) {
		my $comma_pos = index($insn_str, ',');
		my $space_pos = $comma_pos;
		while(substr($insn_str, $space_pos, 1) ne " ") {
		    $space_pos--;
		}
		# printf("comma_pos = $comma_pos, space_pos = $space_pos, ");
		$write_reg = substr($insn_str, $space_pos+1, $comma_pos-$space_pos-1); 
	    }
	    if($write_reg ne "") {
		# printf("reg = $write_reg, ");
		if ( !grep( /^$write_reg$/, @recent_w_regs ) ) {
		    $recent_w_regs[$ind] = $write_reg;
		    $ind = ($ind + 1) % 3;
		}
	    }
	}
	(length $bytes) == 8 || die "ARM32 instructions cannot be more than 8 bytes long";
	my $b1 = substr $bytes, 0, 2;
	my $b2 = substr $bytes, 2, 2;
	my $b3 = substr $bytes, 4, 2;
	my $b4 = substr $bytes, 6, 2;
	# printf(" $b4, $b3, $b2, $b1, // $insn_str\n");
	$frag_contents .= sprintf("$b4 $b3 $b2 $b1\n");
	# print "$line_num*\n\n";
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
# 0 = acsgtdm, adfeq
# 1 = adc, add, asr, 
# 2 = and, 
# 3 = b

sub get_bucket () {
    my $mnemonic = shift(@_);
    if($mnemonic =~ /^adc/) 
    { return 1; }
    elsif ($mnemonic =~ /^cmp/) 
    { return 2; }
}
