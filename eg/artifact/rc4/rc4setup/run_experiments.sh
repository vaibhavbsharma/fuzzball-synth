#!/bin/bash
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-rc4-mo-setup.pl 1328 1329 1 1 -1 15 |& tee logs/synth-rc4-mo-setup-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-rc4-om-setup.pl 1329 1328 1 1 -1 15 |& tee logs/synth-rc4-om-setup-new.log
