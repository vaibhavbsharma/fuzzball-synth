#!/bin/bash

# populates bucket directories for each kind of Glibc experiment

if [[ $# -ne 1 ]]; then
  echo "$0: usage: setup_exps_hth.sh <adapter family, 1=argsub+retvalsub, 2=typeconv+retvalsub, 3=arithmetic-int+retvalsub, 4=memsub+argsub+retvalsub>"
  exit 1
fi
FUZZBALL_SYNTH=/export/scratch/vaibhav/fuzzball-synth && export FUZZBALL_SYNTH

if [[ $1 -eq 4 ]]; then
    export NUM_DIRS=16
    export SUBDIR="memsub";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/memsub/synth-memsub.pl
    export BINARY=$FUZZBALL_SYNTH/eg/libc/memsub/two-funcs
    export TYPESFILE=$FUZZBALL_SYNTH/eg/libc/memsub/types-no-float-1204-one-struct.lst
elif [[ $1 -eq 3 ]]; then
    export NUM_DIRS=32
    export SUBDIR="arith";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/arithmetic/synth-arithmetic
    export BINARY=$FUZZBALL_SYNTH/eg/libc/arithmetic/two-funcs
    export TYPESFILE=$FUZZBALL_SYNTH/eg/libc/arithmetic/types-no-float-1204.lst
elif [[ $1 -eq 2 ]]; then
    export NUM_DIRS=32
    export SUBDIR="typeconv";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/simple/synth-typeconv.pl
    export BINARY=$FUZZBALL_SYNTH/eg/libc/arithmetic/two-funcs
    export TYPESFILE=$FUZZBALL_SYNTH/eg/libc/arithmetic/types-no-float-1204.lst
else
    export NUM_DIRS=32
    export SUBDIR="argsub";
    export DRIVER=$FUZZBALL_SYNTH/eg/libc/simple/synth-argsub.pl
    export BINARY=$FUZZBALL_SYNTH/eg/libc/arithmetic/two-funcs
    export TYPESFILE=$FUZZBALL_SYNTH/eg/libc/arithmetic/types-no-float-1204.lst
fi

REFS_BASE_DIR=/export/scratch/vaibhav/glibc-exps/$SUBDIR && export REFS_BASE_DIR
LOG_FILE=1.log && export LOG_FILE
ERROR_LOG_FILE=1.error.log && export LOG_FILE


for ((j=1; j<=$NUM_DIRS; j++)); do
    # populate files
    cp $FUZZBALL_SYNTH/eg/libc/exp-scripts/run-funcs.pl $REFS_BASE_DIR/glibc-$j/;
    cp $DRIVER $REFS_BASE_DIR/glibc-$j/;
    cp $BINARY $REFS_BASE_DIR/glibc-$j/;
    cp $TYPESFILE $REFS_BASE_DIR/glibc-$j/;
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
