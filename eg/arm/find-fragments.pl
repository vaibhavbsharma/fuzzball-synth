#!/usr/bin/perl

use strict;

die "Usage: find-fragments.pl <path-to-dump-file> <output-dir>"
  unless @ARGV == 2;
my ($dump_file,$output_dir) = @ARGV;
my @insns = ();

my $fragment_count=0;
my %frag_insn_count=();

for(my $i = 0; $i <= 20; $i++) {
    $frag_insn_count{$i} = 0;
}

sub a_fragment
{
    my $starting_line_num = shift(@_);
    my $ending_line_num = shift(@_);
    my @branch_targets = @_;
    my $this_fragment_insns = "";
    for(my $j = $starting_line_num; $j <= $ending_line_num; $j++) {
	# printf("$insns[$j]");
	$this_fragment_insns .= $insns[$j];
    }
    my $contains_branches = 1;
    for(my $i = 0; $i < scalar(@branch_targets); $i++) {
	# printf("branch target = $branch_targets[$i]\n");
	if(index($this_fragment_insns, $branch_targets[$i].":") == -1) {
	    $contains_branches = 0;
	    last;
	}
    }
    if($contains_branches == 1) {
	my $a = $starting_line_num + 1;
	my $b = $ending_line_num + 1;
	# printf("fragment at ($a, $b)\n");
	# printf("$this_fragment_insns");

	my $output = `perl create-fragments.pl $dump_file $output_dir/ $a $b`;
	printf("$output");

	$fragment_count++;
	$frag_insn_count{$b - $a}++;
    }
}

my $line_num = -1;
my $text_section = 0;
my $max_fragment_size = 20;

open(F, "<$dump_file") or die;
while (<F>) {
    push @insns, $_;
}

foreach (@insns) {
    $line_num++;
    # printf("$line_num: $_");
    if(/.*Disassembly of section .text.*$/) {
	$text_section = 1;
    }
    if($text_section == 0) { next; }
    if(!/ ([0-9a-f]+):  ([0-9a-f]+)   (.*)$/) { next; }
    if(/.*nop.*/) { next; }
    if( /.*bx  lr.*/ # return 
	|| /.*ldr.*/  || /.*ldm.*/ 
	|| /.*str.*/  || /.*stm.*/
	|| /.*push.*/ || /.*pop.*/
	|| (has_cc_string($_, "bl") == 1)
	|| (has_cc_string($_, "blx") == 1)
	|| (has_cc_string($_, "bx") == 1)
	|| (has_coproc_insn($_) == 1)
	) {
	next; 
    }
    my $starting_line_num = $line_num;
    my @branch_targets = ();
    for(my $j = $starting_line_num; $j < $starting_line_num + $max_fragment_size; $j++) {
	if( (!($insns[$j]=~/ ([0-9a-f]+):  ([0-9a-f]+)   (.*)$/))) {
	    # printf("breaking at the end\n");
	    last;
	}
	if( ($insns[$j]=~/.*bx  lr.*/) # return 
	    || ($insns[$j]=~/.*ldr.*/) || ($insns[$j]=~/.*ldm.*/) 
	    || ($insns[$j]=~/.*str.*/) || ($insns[$j]=~/.*stm.*/)
	    || ($insns[$j]=~/.*push.*/) || ($insns[$j]=~/.*pop.*/)
	    || (has_cc_string($insns[$j], "bl") == 1)
	    || (has_cc_string($insns[$j], "blx") == 1)
	    || (has_cc_string($insns[$j], "bx") == 1)
	    || (has_coproc_insn($insns[$j]) == 1)
	    ) {
	    # printf("breaking because of exit point ($insns[$j])\n");
	    last; 
	}
	if($insns[$j]=~/.* beq (.*) (.*)$/ ||  
	   $insns[$j]=~/.* bne (.*) (.*)$/ ||
	   $insns[$j]=~/.* bcs (.*) (.*)$/ ||
	   $insns[$j]=~/.* bhs (.*) (.*)$/ ||
	   $insns[$j]=~/.* bcc (.*) (.*)$/ ||
	   $insns[$j]=~/.* blo (.*) (.*)$/ ||
	   $insns[$j]=~/.* bmi (.*) (.*)$/ ||
	   $insns[$j]=~/.* bpl (.*) (.*)$/ ||
	   $insns[$j]=~/.* bvs (.*) (.*)$/ ||
	   $insns[$j]=~/.* bvc (.*) (.*)$/ ||
	   $insns[$j]=~/.* bhi (.*) (.*)$/ ||
	   $insns[$j]=~/.* bls (.*) (.*)$/ ||
	   $insns[$j]=~/.* bge (.*) (.*)$/ ||
	   $insns[$j]=~/.* blt (.*) (.*)$/ ||
	   $insns[$j]=~/.* bgt (.*) (.*)$/ ||
	   $insns[$j]=~/.* ble (.*) (.*)$/ ||
	   $insns[$j]=~/.* bal (.*) (.*)$/)  {
	    # printf("branch target = $1");
	    push @branch_targets, $1;
	}
	a_fragment($starting_line_num, $j, @branch_targets);
    }
}

printf("total number of fragments = $fragment_count\n");
#while(my($k, $v) = each %frag_insn_count) {
foreach my $k (sort {$a <=> $b} keys %frag_insn_count) { 
    printf("k = $k, v = $frag_insn_count{$k}\n");
}

sub has_coproc_insn () {
    my $line = shift(@_);
    my @coproc_insn = ("ldc","stc","cdp","mcr","mrc","mrrc","msr","mrs","sys","mar","mra","bfi","bfc","bkpt");
    foreach my $str (@coproc_insn) {
	if(has_cc_string($line, $str) == 1) { return 1; }
    }
    return 0;
}

sub has_cc_string () {
    my $line = shift(@_);
    my $cmd = shift(@_);
    my @cc = ("eq","ne","cs","hs","cc","lo","mi","pl","vs","vc","hi","ls","ge","lt","gt","le","al");
    if(index($line, ($cmd . " ")) != -1) { return 1; }
    foreach my $cc_str (@cc) {
	my $str = $cmd . $cc_str;
	if(index($line, $str) != -1) { return 1; }
    }
    return 0;
}


