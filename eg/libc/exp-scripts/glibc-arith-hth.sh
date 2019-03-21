#!/bin/bash

export ESVHOME=/export/scratch/vaibhav

if [[ $# -ne 1 || $1 -gt 32 || $1 -lt 1 ]]; then
  echo "$0: usage: glibc-arith-hth.sh <index of bucket to initialize between 1 and 32>"
  exit 1
fi

export BUCKET=$1
screen -S "glibc-$BUCKET" -dm bash -c '
cd $ESVHOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$ESVHOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log'
echo "Started screen with handle glibc-$BUCKET";
wait
