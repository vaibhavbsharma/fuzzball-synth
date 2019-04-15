#!/bin/bash

export ESVHOME=/export/scratch2/vaibhav

if [[ $# -ne 2 || $2 -gt 32 || $2 -lt 1 ]]; then
  echo "$0: usage: run-glibc-exps.sh <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int, 4=memsub> <index of bucket to initialize between 1 and 32 or between 1 and 16 for memsub>"
  exit 1
fi

export BUCKET=$2
export ADAPTER_FAMILY=$1
if [[ $ADAPTER_FAMILY -eq 4 ]]; then
    export SUBDIR="memsub"
    export NUM_BUCKETS=16
elif [[ $ADAPTER_FAMILY -eq 3 ]]; then
    export SUBDIR="arith"
    export NUM_BUCKETS=32
elif [[ $ADAPTER_FAMILY -eq 2 ]]; then
    export SUBDIR="typeconv"
    export NUM_BUCKETS=32
else
    export SUBDIR="argsub"
    export NUM_BUCKETS=32
fi
SCREENHANDLE="glibc-$SUBDIR-$BUCKET"
screen -S $SCREENHANDLE -dm bash -c '
cd $ESVHOME/glibc-exps/$SUBDIR/glibc-$BUCKET;
FUZZBALL_LOC=$ESVHOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs.pl $NUM_BUCKETS $BUCKET $ADAPTER_FAMILY -1 255 >> logs/1.log 2>logs/1.error.log'
if [[ $? -eq 0 ]]; then 
    echo "Started screen with handle $SCREENHANDLE";
else
    echo "Failed to start screen $SCREENHANDLE";
fi
wait
