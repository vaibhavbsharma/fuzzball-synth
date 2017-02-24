#!/bin/bash
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-bn.pl 1334 1335 1 1 -1 34 |& tee synth-bn-new.log
