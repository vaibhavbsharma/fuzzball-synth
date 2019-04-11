#!/bin/bash

if [[ $# -ne 4 ]]; then
  echo "$0: usage: setup_exps.sh <base dir containing arm-<1-num dirs> dirs> <num dirs> <log file> <1 to delete old logs, 0 otherwise>"
  exit 1
fi
FUZZBALL_SYNTH=/home/smccaman/vaibhav/fuzzball-synth && export FUZZBALL_SYNTH
REFS_BASE_DIR=$1
NUM_ARM_DIRS=$2 && export NUM_ARM_DIRS
LOG_FILE=$3 && export LOG_FILE


echo "started processing $REFS_BASE_DIR";
for ((j=1; j<=$NUM_ARM_DIRS; j++)); do
	# populate files
	cp $FUZZBALL_SYNTH/eg/arm/run-fragments-msi.pl $REFS_BASE_DIR/arm-$j/;
	cp $FUZZBALL_SYNTH/eg/arm/synth-typeconv-frag.pl $REFS_BASE_DIR/arm-$j/;
	cp $FUZZBALL_SYNTH/eg/arm/synth-argsub-frag.pl $REFS_BASE_DIR/arm-$j/;  
	cp $FUZZBALL_SYNTH/eg/arm/synth-arithmetic-frag.pl $REFS_BASE_DIR/arm-$j/;  
	cp $FUZZBALL_SYNTH/eg/arm/test_arm  $REFS_BASE_DIR/arm-$j/; 
	cp $FUZZBALL_SYNTH/eg/arm/types-no-float-1204.lst  $REFS_BASE_DIR/arm-$j/;  
	cp $FUZZBALL_SYNTH/eg/arm/constant-bounds.lst  $REFS_BASE_DIR/arm-$j/;
	# delete checkpointing files and temporary files
	rm $REFS_BASE_DIR/arm-$j/don* 2>/dev/null;
	rm $REFS_BASE_DIR/arm-$j/checkpoint 2>/dev/null;
	rm -rf $REFS_BASE_DIR/arm-$j/fuzzball-tmp-* 2>/dev/null;
	rm $REFS_BASE_DIR/arm-$j/str_arg* 2>/dev/null;
	# delete log files from an incomplete previous run
	if [[ $4 -eq 1 ]]; then
		rm $REFS_BASE_DIR/arm-$j/logs/$LOG_FILE 2>/dev/null;
		rm $REFS_BASE_DIR/arm-$j/logs/run-fragments-msi.log 2>/dev/null;
	else
		if [[ -e $REFS_BASE_DIR/arm-$j/logs/$LOG_FILE || 
			-e $REFS_BASE_DIR/arm-$j/logs/run-fragments-msi.log ]]; then
			echo "old log files still exist which you may want to delete";
		else
			echo "old log files dont exist in $REFS_BASE_DIR/arm-$j";
		fi;
	fi;	
done;
