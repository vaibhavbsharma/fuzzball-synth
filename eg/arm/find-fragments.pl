#!/usr/bin/perl

use strict;

die "Usage: find-fragments.pl <path-to-dump-file>"
  unless @ARGV == 1;
my ($dump_file) = @ARGV;
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

	# my $output; # = `perl create-fragments.pl $dump_file fragments/ $a $b`;
	# printf("$output");

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
	|| /.*mcr.*/ # move to coprocessor from ARM reg(s)
	|| /.*mrc.*/ # move to ARM reg from coprocessor
	|| /.*msr.*/ # move to system coprocessor reg from ARM reg 
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
	    || ($insns[$j]=~/.*mcr.*/) # move to coprocessor from ARM reg(s)
	    || ($insns[$j]=~/.*mrc.*/) # move to ARM reg from coprocessor
	    || ($insns[$j]=~/.*msr.*/) # move to system coprocessor reg from ARM reg 
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
	   $insns[$j]=~/.* bal (.*) (.*)$/) {
	    # printf("branch target = $1");
	    push @branch_targets, $1;
	}
	a_fragment($starting_line_num, $j, @branch_targets);
    }
}

printf("total number of fragments = $fragment_count\n");
while(my($k, $v) = each %frag_insn_count) { 
    printf("k = $k, v = $v\n");
}
