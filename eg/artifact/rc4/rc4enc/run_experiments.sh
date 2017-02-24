#!/bin/bash
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-mo-enc.pl 1326 1327 1 1 -1 15 |& tee logs/synth-mo-enc-new.log
LD_LIBRARY_PATH=`pwd`/../../lib/:$LD_LIBRARY_PATH perl synth-om-enc.pl 1327 1326 1 1 -1 15 |& tee logs/synth-om-enc-new.log
