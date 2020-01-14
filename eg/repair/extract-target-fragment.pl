#!/usr/bin/perl

use strict;

die "Usage: extract-target-fragment.pl <log-file-with-callstacks>"
  unless @ARGV == 1;
my($log_file) = @ARGV;


open (FILE, $log_file);
my ($syscall_callstack_tracing, $eip_callstack_tracing) = (0,0);
my (@syscall_callstack, @eip_callstack);
while (<FILE>) {
    if (/^tracing entire callstack on syscall(.*)$/) {
	$syscall_callstack_tracing = 1;
	@syscall_callstack = ();
	# print $_;
    }
    elsif ($syscall_callstack_tracing == 1) {
	if (/([0-9]+): (0x[0-9a-f]+) to (0x[0-9a-f]+)/) {
	    push @syscall_callstack, $_;
	    # print $_;
	} else { $syscall_callstack_tracing = 0; }
    }
    elsif (/^tracing entire callstack at eip = (0x[0-9a-f]+)$/) {
	$eip_callstack_tracing = 1;
	@eip_callstack = ();
	# print $_;
    }
    elsif ($eip_callstack_tracing == 1) {
	if (/([0-9]+): (0x[0-9a-f]+) to (0x[0-9a-f]+)/) {
	    push @eip_callstack, $_;
	    # print $_;
	} else { 
	    $eip_callstack_tracing = 0;
	    my $min_length = $#eip_callstack < $#syscall_callstack ?
		$#eip_callstack : $#syscall_callstack;
	    my @common_prefix = ();
	    my $i = 0;
	    while ($i <= $min_length) {
		if ($eip_callstack[$i] eq $syscall_callstack[$i]) {
		    push @common_prefix, $eip_callstack[$i];
		} else { last; }
		$i++;
	    }
	    print "common prefix:\n";
	    for my $j (0 .. $#common_prefix) {
		print $common_prefix[$j];
	    }
	    if ($i <= $#eip_callstack) {
		if ($syscall_callstack[$i] =~ /([0-9]+): (0x[0-9a-f]+) to (0x[0-9a-f]+)/) {
		    print "target fragment begins at argument construction before $2\n";
		}
		if ($eip_callstack[$i] =~ /([0-9]+): (0x[0-9a-f]+) to (0x[0-9a-f]+)/) {
		    print "target fragment ends at ". sprintf("0x%08Lx", (hex $2) + 5). "\n";
		}
	    } else {
		if ($syscall_callstack[$i-1] =~ /([0-9]+): (0x[0-9a-f]+) to (0x[0-9a-f]+)/) {
		    print "target fragments begin at argument construction before $2 and ends at " . sprintf("0x%08Lx", (hex $2) + 5) . "\n";
		}
	    }
	}
    }
}
close FILE;
