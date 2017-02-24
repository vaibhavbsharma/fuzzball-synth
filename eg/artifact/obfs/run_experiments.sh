#!/bin/bash
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-ob-clone1.pl 1332 1333 1 1 -1 15 |& tee logs/synth-ob-clone1-new.log
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-ob-clone2.pl 1332 1333 1 1 -1 15 |& tee logs/synth-ob-clone2-new.log
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-ob-clone3-notworking.pl 1332 1333 1 1 -1 15 |& tee logs/synth-ob-clone3-notworking-new.log
LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-ob-clone3-3min.pl 1332 1333 1 1 -1 15 |& tee logs/synth-ob-clone3-3min-new.log
# LD_LIBRARY_PATH=`pwd`/../lib/:$LD_LIBRARY_PATH perl synth-ob-clone3-51min.pl 1332 1333 1 1 -1 15 |& tee logs/synth-ob-clone3-51min-new.log
