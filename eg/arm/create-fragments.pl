#!/usr/bin/perl

use strict;

die "Usage: create-fragments.pl <path-to-dump-file> <fragment-prefix> <starting-line-num> <ending-line-num>"
  unless @ARGV == 4;
my ($dump_file,$file_prefix,$start_num,$end_num) = @ARGV;

# 2, and(2), 
# 4, beq(2), b(2), 
# 4, cmp(4)
# 5, mov(1), movge(2), movlt(2), 
# 15
my $inner_bucket_1 = 0/15;
my $inner_bucket_2 = 2/15;
my $inner_bucket_3 = 4/15;
my $inner_bucket_4 = 4/15;
my $inner_bucket_5 = 5/15;

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
my %bucket_count=();

for(my $i = 0; $i <= 5; $i++) {
    $bucket_count{$i} = 0;
}

open(F, "<$dump_file") or die;
while (<F>) {
    if(($line_num >= $start_num) && ($line_num <= $end_num)) {
	# print("$line_num| $_");
	my $bytes="";
	my $insn_str="";
	my $mnemonic;
	if(/^ *([0-9a-f]+):  ([0-9a-f]+)   (.*)$/) {
	    # printf("address = $1, bytes = $2, ");
	    $bytes = $2; $insn_str = $3;
	    $mnemonic = substr($insn_str, 0, index($insn_str, ' '));
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
	my $bucket = get_bucket($mnemonic);
	# printf("mnemonic($mnemonic) has bucket($bucket)\n");
	$bucket_count{$bucket}++;
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
    my $distance = calc_distance ();
    # printf("distance = $distance\n");
    if($added_ret_reg == 1) {
	my $file_name = $file_prefix . $start_num . "_" . $end_num . "_" . (sprintf("%0.4f",$distance)) . "_" . $file_num . ".frag";
	# printf("file_name = $file_name\n");
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

sub calc_distance () {
    my $total = 0;
    foreach my $k (sort {$a <=> $b} keys %bucket_count) { 
	if($k != 0) { $total += $bucket_count{$k}; }
	# printf("bucket_count{$k} = $bucket_count{$k}\n");
    }
    # printf("total = $total\n");
    my $distance = calc_euclidean_dist($bucket_count{1}/$total,
				       $bucket_count{2}/$total,
				       $bucket_count{3}/$total,
				       $bucket_count{4}/$total,
				       $bucket_count{5}/$total,
				       $inner_bucket_1,
				       $inner_bucket_2,
				       $inner_bucket_3,
				       $inner_bucket_4,
				       $inner_bucket_5);
    return $distance;
}

sub calc_euclidean_dist() {
    my $a1 = shift(@_);
    my $a2 = shift(@_);
    my $a3 = shift(@_);
    my $a4 = shift(@_);
    my $a5 = shift(@_);
    my $b1 = shift(@_);
    my $b2 = shift(@_);
    my $b3 = shift(@_);
    my $b4 = shift(@_);
    my $b5 = shift(@_);
    my $ret = sqrt((($b1-$a1)**2) + 
		   (($b2-$a2)**2) + 
		   (($b3-$a3)**2) + 
		   (($b4-$a4)**2) + 
		   (($b5-$a5)**2));
    return $ret;
}

# printf("recent_w_regs = @recent_w_regs\n");
# 0 = <get from find-fragments has_coproc_insn>
# 1 = adc, add, mul, muls, qdadd, qdsub, rsb, rsbs, rsc, rscs, sbc, sbcs, smlabb, smlabt, smlatb, smtatt, smlabb", "smlad", "smlad", "smlal", "smlalbb", "smlaldx", "smlaltb", "smlaltt", "smlatt", "smlawb", "smlawt", "smlsd","smlsdx", "smmlar", SMLAD, SMLADX, SMLALD, SMLALDX, SMLSD, SMLSDX, SMLSLD, SMLSLDX, SMMLA, SMMLAR, SMMLS, SMMLSR, SMMUL, SMMULR, SMUAD, SMUADX, SMUSD, SMUSDX, smull, smlal, ssubaddx, sub, subs, umlal,   
# 2 = and, asr, asrs, bici, bics, eor, eors, lsl, lsls, lsr, lsrs, mvn, mvns, orr, orrs, ror, ubfx, 
# 3 = b, 
# 4 = cmn, cmp, teq, tst,  
# 5 = mov, movs, movt, movw, nop,  

sub get_bucket () {
    my $mnemonic = shift(@_);
    if($mnemonic =~ /^adc/ || 
       $mnemonic =~ /^add/  ||
       $mnemonic =~ /^mul/  ||
       $mnemonic =~ /^muls/  ||
       $mnemonic =~ /^qdadd/  ||
       $mnemonic =~ /^qdsub/  ||
       $mnemonic =~ /^rsb/  ||
       $mnemonic =~ /^rsbs/  ||
       $mnemonic =~ /^rsc/  ||
       $mnemonic =~ /^rscs/  ||
       $mnemonic =~ /^sbc/  ||
       $mnemonic =~ /^sbcs/  ||
       $mnemonic =~ /^smlabb/  ||
       $mnemonic =~ /^smlabt/  ||
       $mnemonic =~ /^smlatb/  ||
       $mnemonic =~ /^smtatt/  ||
       $mnemonic =~ /^smlabb/  ||
       $mnemonic =~ /^smlad/  ||
       $mnemonic =~ /^smlad/  ||
       $mnemonic =~ /^smlal/  ||
       $mnemonic =~ /^smlalbb/  ||
       $mnemonic =~ /^smlaldx/  ||
       $mnemonic =~ /^smlaltb/  ||
       $mnemonic =~ /^smlaltt/  ||
       $mnemonic =~ /^smlatt/  ||
       $mnemonic =~ /^smlawb/  ||
       $mnemonic =~ /^smlawt/  ||
       $mnemonic =~ /^smlsd/  ||
       $mnemonic =~ /^smlsdx/  ||
       $mnemonic =~ /^smmlar/  ||
       $mnemonic =~ /^SMLAD/  ||
       $mnemonic =~ /^SMLADX/  ||
       $mnemonic =~ /^SMLALD/  ||
       $mnemonic =~ /^SMLALDX/  ||
       $mnemonic =~ /^SMLSD/  ||
       $mnemonic =~ /^SMLSDX/  ||
       $mnemonic =~ /^SMLSLD/  ||
       $mnemonic =~ /^SMLSLDX/  ||
       $mnemonic =~ /^SMMLA/  ||
       $mnemonic =~ /^SMMLAR/  ||
       $mnemonic =~ /^SMMLS/  ||
       $mnemonic =~ /^SMMLSR/  ||
       $mnemonic =~ /^SMMUL/  ||
       $mnemonic =~ /^SMMULR/  ||
       $mnemonic =~ /^SMUAD/  ||
       $mnemonic =~ /^SMUADX/  ||
       $mnemonic =~ /^SMUSD/  ||
       $mnemonic =~ /^SMUSDX/  ||
       $mnemonic =~ /^smull/  ||
       $mnemonic =~ /^smlal/  ||
       $mnemonic =~ /^ssubaddx/  ||
       $mnemonic =~ /^sub/  ||
       $mnemonic =~ /^subs/  ||
       $mnemonic =~ /^umlal/ ) 
    { return 1; }
    elsif ($mnemonic =~ /^and/  ||
	   $mnemonic =~ /^asr/  ||
	   $mnemonic =~ /^asrs/  ||
	   $mnemonic =~ /^bici/  ||
	   $mnemonic =~ /^bics/  ||
	   $mnemonic =~ /^eor/  ||
	   $mnemonic =~ /^eors/  ||
	   $mnemonic =~ /^lsl/  ||
	   $mnemonic =~ /^lsls/  ||
	   $mnemonic =~ /^lsr/  ||
	   $mnemonic =~ /^lsrs/  ||
	   $mnemonic =~ /^mvn/  ||
	   $mnemonic =~ /^mvns/  ||
	   $mnemonic =~ /^orr/  ||
	   $mnemonic =~ /^orrs/  ||
	   $mnemonic =~ /^ror/  ||
	   $mnemonic =~ /^ubfx/)
    { return 2; }
    elsif ($mnemonic =~ /^cmn/ || 
	   $mnemonic =~ /^cmp/ ||
	   $mnemonic =~ /^teq/ ||
	   $mnemonic =~ /^tst/) { return 4; }
    elsif ($mnemonic =~ /^mov/ || 
	   $mnemonic =~ /^movs/ ||
	   $mnemonic =~ /^movt/ ||
	   $mnemonic =~ /^movw/ ||
	   $mnemonic =~ /^nop/) { return 5; }
    elsif (is_ignored_mnemonic($mnemonic) == 1) { return 0; }
    elsif ($mnemonic =~ /^b/) { return 3; }
}

sub is_ignored_mnemonic () {
    my $mn = shift(@_);
    my @coproc_insn = 
	("ldc","stc","cdp","mcr","mrc","mrrc","msr","mrs","sys","mar","mra","bfi","bfc","bkpt",
	 "cfcmp64","cfmadd32","cfmsub32", "cfmsuba32","cfmul32","cfmuld","cfmvrs","cfsh64","cfsub","cfadd",
	 "ldfcse", "ldfcss", "ldfd", "ldfeqp", "ldfeqs", "ldfgte", "ldflee", "ldflse", "ldfmie", "ldfmis", 
	 "ldfnep", "ldfnes", "ldfvce", "ldfvcs", "ldfvse", "ldfvss", "mla","mnfsp","mvfe",
	 "pld","pldw","pli", "polltsp", "powvsem","powvsem", "rndnes","shsub16","shsub8","shadd16","shadd8",
	 "shsubaddx","smc", "sqt", "ssat", "stfc", "stfg", "stfh", "stfl", "stfm", "stfn", "stfs", 
	 "sufcse", "sufcs", "svc", "umaal", "umull", "uqsub16", "usada8", "usat", "usub8",
	 "vaba.u16", "vabdl.u32", "vceq.i8", "vcge.s", "vcgt.u16", "vcgt.u", 
	 "vcvteq.f64.f32", "vdupcs.8", "vext.8", "vhadd.u8", "vld1.8", "vld2.16", 
	 "vld3", "vld4.16", "vld4.32", "vld4.8", "vmax.f32", "vmin.s16", "vmlacc.f64", 
	 "vmls.i16", "vmls.i8", "vmlsl.u32", "vmlsmi.f32", "vmov.16", "vmovcc.8", 
	 "vmovcs.s8", "vmovle.32", "vmovle.u8", "vmovne.u8", "vmovvs.8", "vmul.f32", 
	 "vmul.i", "vmull.s32", "vnmlsle.f64", "vnmulmi.f64", "vnmulvs.f64", 
	 "vpadd.f", "vpmin.u16", "vpmin.u8", "vqdmulh.s32", "vqrshl.s8", 
	 "vqsub.s16", "vqsub.u8", "vraddhn.i32", "vrhadd.u8", "vrshr.u64", 
	 "vsli.64", "vsra.s32", "vsri.64", "vst1.16", "vst3", "vst4.16", 
	 "vst4", "vsubgt.f32", "vsubhn.i64",
	 "stcl", "stfv"
	);
    foreach my $str (@coproc_insn) {
	if($str eq $mn) { return 1; }
    }
    return 0;
}
