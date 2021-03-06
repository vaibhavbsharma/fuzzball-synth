#!/bin/bash
cd simple-1;
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-one.pl 1055 1056 1 1 -1 15 |& tee ../logs/wait-waitpid-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-one.pl 1055 1058 1 1 -1 15 |& tee ../logs/wait-wait4-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-one.pl 1056 1058 1 1 -1 15 |& tee ../logs/waitpid-wait4-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-one.pl 1055 1057 1 1 -1 15 |& tee ../logs/wait-wait3-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-one.pl 1057 1058 1 1 -1 15 |& tee ../logs/wait3-wait4-new.log
cd ../typeconv-1;
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-typeconv.pl 904 905 1 1 -1 15 |& tee ../logs/ffs-ffsl-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-typeconv.pl 677 678 1 1 -1 15 |& tee ../logs/abs-labs-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-typeconv.pl 135 136 1 1 -1 15 |& tee ../logs/recv-recvfrom-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-typeconv.pl 138 140 1 1 -1 15 |& tee ../logs/send-sendto-new.log;
cd ..;
