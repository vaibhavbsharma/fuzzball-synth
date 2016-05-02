Code in this directory was authored by the University of Minnesota.

University of Minnesota Proprietary Information per CFAR ACA.
Copyright (C) 2015, University of Minnesota
University of Minnesota's development of non-commercial software is
provided to the Government with Unlimited Rights under the terms of
the contract.

This directory contains a variety of examples using FuzzBALL for
adaptor search and synthesis. The directories are organized as
follows:

arithmetic - Arithmetic adaptors
dossify - Using FuzzBALL to search for multi-variant attacks
itoa - Integer-to-string conversion clone from CROMU_00001
libc/types-gdb - Ground-truth type information for the GNU C library
libc/simple - Simple and type conversion adaptors applied to glibc
libc/arithmetic - Arithmetic adaptors a applied to glibc
low-bit - A pedagogic example of a simple adaptor
palindrome-tr - Character set translation applied to a palindrome
                checking example
simple-len - Buffer-length argument adaptor

The tools are implemented as wrappers around FuzzBALL, so they depend
on the FEVIS-enhanced version of FuzzBALL being available: generally
it can either be under "tools/fuzzball", or it and the STP decision
procedure can be referenced with respective FUZZBALL_LOC and STP_LOC
environment variables. Scripts ending in .pl are written in Perl, and
so should not require any compilation. Programs ending in .ml should
be compiled with ocamlc or interpreted with ocaml, while programs
ending in .cpp should be compiled with a C++ compiler such as g++. The
subject programs should be compiled for Linux/x86-64 with symbol
information.

For each sub-directory, the top-level program or the next file to
consult is as follows:

arithmetic: run_tests.sh
dossify: README
itoa: synth-one.pl
libc/types-gdb: README
libc/simple: synth-demo.pl (short demonstration)
             synth.pl (full experiment)
             synth-typeconv.pl (experiment with type conversion)
libc/arithmetic: synth-arithmetic.ml
low-bit: README
palindrome-tr: synth.ml
simple-len: synth.ml
