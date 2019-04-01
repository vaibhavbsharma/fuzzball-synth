#!/bin/bash

export ESVHOME=/export/scratch/vaibhav

if [[ $# -ne 2 || $2 -gt 32 || $2 -lt 1 ]]; then
  echo "$0: usage: glibc-arith-hth.sh <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int> <index of bucket to initialize between 1 and 32>"
  exit 1
fi

export BUCKET=$1
if [[ $1 -eq 3 ]]; then
    export SUBDIR="arith";
elif [[ $1 -eq 2 ]]; then
    export SUBDIR="typeconv";
else
    export SUBDIR="argsub";
fi
SCREENHANDLE="glibc-$SUBDIR-$BUCKET"
screen -S $SCREENHANDLE -dm bash -c '
cd $ESVHOME/glibc-exps/$SUBDIR/glibc-$BUCKET;
FUZZBALL_LOC=$ESVHOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET $1 -1 255 >> logs/1.log'
echo "Started screen with handle $SCREENHANDLE";
wait
