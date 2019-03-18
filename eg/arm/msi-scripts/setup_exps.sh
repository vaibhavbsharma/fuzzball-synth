#!/bin/bash

FUZZBALL_SYNTH=/home/smccaman/vaibhav/fuzzball-synth && export FUZZBALL_SYNTH
NUM_ARM_DIRS=32 && export NUM_ARM_DIRS
REFS_BASE_DIR=/home/smccaman/vaibhav && export REFS_BASE_DIR
START_REF_NUM=1 && export START_REF_NUM
END_REF_NUM=25 && export END_REF_NUM
LOG_FILE=13.log && export LOG_FILE


for ((i=$START_REF_NUM; i<=$END_REF_NUM; i++)); do
	echo -n "started processing ref$i";
	for ((j=1; j<=$NUM_ARM_DIRS; j++)); do
		# populate files
  	cp $FUZZBALL_SYNTH/eg/arm/run-fragments-msi.pl $REFS_BASE_DIR/ref$i/arm-$j/;
  	cp $FUZZBALL_SYNTH/eg/arm/synth-typeconv-frag.pl $REFS_BASE_DIR/ref$i/arm-$j/;
  	cp $FUZZBALL_SYNTH/eg/arm/synth-argsub-frag.pl $REFS_BASE_DIR/ref$i/arm-$j/;  
  	cp $FUZZBALL_SYNTH/eg/arm/synth-arithmetic-frag.pl $REFS_BASE_DIR/ref$i/arm-$j/;  
  	cp $FUZZBALL_SYNTH/eg/arm/test_arm  $REFS_BASE_DIR/ref$i/arm-$j/; 
  	cp $FUZZBALL_SYNTH/eg/arm/types-no-float-1204.lst  $REFS_BASE_DIR/ref$i/arm-$j/;  
  	cp $FUZZBALL_SYNTH/eg/arm/constant-bounds.lst  $REFS_BASE_DIR/ref$i/arm-$j/;
		# delete checkpointing files and temporary files
		rm $REFS_BASE_DIR/ref$i/arm-$j/don* 2>/dev/null;
		rm $REFS_BASE_DIR/ref$i/arm-$j/checkpoint 2>/dev/null;
		rm -rf $REFS_BASE_DIR/ref$i/arm-$j/fuzzball-tmp-* 2>/dev/null;
		rm $REFS_BASE_DIR/ref$i/arm-$j/str_arg* 2>/dev/null;
		# delete log files from an incomplete previous run
		rm $REFS_BASE_DIR/ref$i/arm-$j/logs/$LOG_FILE 2>/dev/null;
		rm $REFS_BASE_DIR/ref$i/arm-$j/logs/run-fragments-msi.log 2>/dev/null;
  done;
	echo ", finished processing ref$i";
done
