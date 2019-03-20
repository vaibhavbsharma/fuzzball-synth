#!/bin/bash -l        
#PBS -l walltime=04:00:00,nodes=2:ppn=8,pmem=2gb 
#PBS -m abe 
#PBS -M vaibhav@umn.edu
#PBS -o $HOME/glibc-exps/output-81-$PBS_JOBID.log
#PBS -e $HOME/glibc-exps/error-81-$PBS_JOBID.log

export BUCKET=$((0*16+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &

BUCKET=$((BUCKET+1))
cd $HOME/glibc-exps/glibc-$BUCKET;
FUZZBALL_LOC=$HOME/fuzzball-adaptorsynth/exec_utils/fuzzball perl ./run-funcs-msi.pl 32 $BUCKET 3 -1 255 >> logs/1.log &


wait
