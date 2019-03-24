#!/bin/bash

if [ $# -lt 5 ]; then
	echo "Your command line contains $# arguments";
	echo "Usage: ./report-all-adapters.sh <dir. containing the ref<1-K> directories, e.g. /home/smccaman/vaibhav> <starting number for ref directories, e.g. 1> <ending number for ref directories, e.g. 25> <number of bucket dirs inside each ref dir, e.g. 32> <log file inside each ref-K/arm-N/logs/ dir., e.g. 13.log> [delete existing refK_arith_adapters.lst=1]";
	echo "Sample usage: ./report-all-adapters.sh /home/smccaman/vaibhav 1 25 32 13.log";
	echo "Sample usage: ./report-all-adapters.sh /home/smccaman/vaibhav 1 25 32 13.log 1 #deletes existing adapter lists";
	exit 1;
fi
REFS_DIR=$1 # /home/smccaman/vaibhav
START_REF_NUM=$2 && export START_REF_NUM # 1
END_REF_NUM=$3 && export END_REF_NUM # 25
NUM_DIRS=$4 # 32
LOG_FILE=$5 # 13.log

# if any ref<K>/ref<K>_arith_adapters.lst already exists, then stop
for ((i=$START_REF_NUM; i<=$END_REF_NUM; i++)); do
	if [ -f "$REFS_DIR/ref$i/ref$((i))_arith_adapters.lst" ]; then
		echo "warning: $REFS_DIR/ref$i/ref$((i))_arith_adapters.lst already exists";
		if [ $6 -eq 1 ]; then
			echo "deleting";
			rm $REFS_DIR/ref$i/ref$((i))_arith_adapters.lst;
		else
			echo "exiting";
			exit 1;
		fi
	fi
done;

for ((i=$START_REF_NUM; i<=$END_REF_NUM; i++)); do
	echo "generating $REFS_DIR/ref$i/ref$((i))_arith_adapters.lst";
	for ((j=1; j<=$NUM_DIRS; j++)); do
		# need 
		grep "Final adaptor" $REFS_DIR/ref$i/arm-$j/logs/$LOG_FILE |& cut -d ' ' -f 7-87  >$REFS_DIR/ref$i/ref$((i))_arith_adapters.lst; 
	done;
	echo "done";
done
