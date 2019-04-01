#!/bin/bash

if [[ $# -ne 1 ]]; then
  echo "$0: usage: setup_exps_hth.sh <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int>"
  exit 1
fi
FUZZBALL_SYNTH=/export/scratch/vaibhav/fuzzball-synth && export FUZZBALL_SYNTH
if [[ $1 -eq 3 ]]; then
    export SUBDIR="arith";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/arithmetic/synth-arithmetic
elif [[ $1 -eq 2 ]]; then
    export SUBDIR="typeconv";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/simple/synth-typeconv.pl
else
    export SUBDIR="argsub";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/simple/synth-argsub.pl
fi

NUM_DIRS=32 && export NUM_DIRS
REFS_BASE_DIR=/export/scratch/vaibhav/glibc-exps/$SUBDIR && export REFS_BASE_DIR
LOG_FILE=1.log && export LOG_FILE
ERROR_LOG_FILE=1.error.log && export LOG_FILE


for ((j=1; j<=$NUM_DIRS; j++)); do
    # populate files
    cp $FUZZBALL_SYNTH/eg/libc/exp-scripts/run-funcs.pl $REFS_BASE_DIR/glibc-$j/;
    cp $DRIVER $REFS_BASE_DIR/glibc-$j/;  
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/two-funcs  $REFS_BASE_DIR/glibc-$j/; 
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/types-no-float-1204.lst  $REFS_BASE_DIR/glibc-$j/;  
    # delete checkpointing files and temporary files
    rm $REFS_BASE_DIR/glibc-$j/don* 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/checkpoint 2>/dev/null;
    rm -rf $REFS_BASE_DIR/glibc-$j/fuzzball-tmp-* 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/str_arg* 2>/dev/null;
    # delete log files from an incomplete previous run
    rm $REFS_BASE_DIR/glibc-$j/logs/$LOG_FILE 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/logs/$ERROR_LOG_FILE 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/logs/run-funcs.log 2>/dev/null;
done;
