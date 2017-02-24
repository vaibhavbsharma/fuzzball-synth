#!/bin/bash
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-mm.pl 1330 1331 1 1 -1 15 |& tee synth-mm-new.log
