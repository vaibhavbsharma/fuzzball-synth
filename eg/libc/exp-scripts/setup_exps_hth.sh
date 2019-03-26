#!/bin/bash

FUZZBALL_SYNTH=/export/scratch/vaibhav/fuzzball-synth && export FUZZBALL_SYNTH
NUM_DIRS=32 && export NUM_DIRS
REFS_BASE_DIR=/export/scratch/vaibhav/glibc-exps && export REFS_BASE_DIR
LOG_FILE=1.log && export LOG_FILE


for ((j=1; j<=$NUM_DIRS; j++)); do
    # populate files
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/run-funcs-msi.pl $REFS_BASE_DIR/glibc-$j/;
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/synth-arithmetic $REFS_BASE_DIR/glibc-$j/;  
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/two-funcs  $REFS_BASE_DIR/glibc-$j/; 
    cp $FUZZBALL_SYNTH/eg/libc/arithmetic/types-no-float-1204.lst  $REFS_BASE_DIR/glibc-$j/;  
    # delete checkpointing files and temporary files
    rm $REFS_BASE_DIR/glibc-$j/don* 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/checkpoint 2>/dev/null;
    rm -rf $REFS_BASE_DIR/glibc-$j/fuzzball-tmp-* 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/str_arg* 2>/dev/null;
    # delete log files from an incomplete previous run
    rm $REFS_BASE_DIR/glibc-$j/logs/$LOG_FILE 2>/dev/null;
    rm $REFS_BASE_DIR/glibc-$j/logs/run-funcs-msi.log 2>/dev/null;
done;
