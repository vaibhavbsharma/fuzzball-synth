#!/bin/sh

if [[ $# -ne 4 ]]; then
  echo "$0: usage: harvest-results.sh <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int> <log file to search through, e.g. 1.log> <prefix directory containing the argsub/typeconv/arith subdirectories, e.g. /export/scratch/vaibhav/glibc-exps> <number of bucket directories expected in prefix-directory/argsub or typeconv or arith/, e.g. 32>"
  exit 1
fi

ADAPTER_FAMILY=$1
LOGFILE=$2
PREFIX_DIR=$3
num_dirs=$4;
g_inequivalent=0;
g_adaptors=0;
g_missing=0;
g_killed=0;
g_total=0;
g_strange_term=0;
suffix="";
echo -e '#\tIneq\t\t#adpt\tTimeout\tf1_crash\ttotal';
if [[ $ADAPTER_FAMILY -eq 3 ]]; then
    export SUBDIR="arith";
elif [[ $ADAPTER_FAMILY -eq 2 ]]; then
    export SUBDIR="typeconv";
else
    export SUBDIR="argsub";
fi

for ((i=1; i<=num_dirs; i++)); do
    FILE=$PREFIX_DIR/$SUBDIR/glibc-$i/logs/$LOGFILE
    inequivalent=`grep 'not equivalent' $FILE | wc -l`; 
    adaptors=`grep 'Final adaptor' $FILE | wc -l`; 
    missing=`grep 'Missing results' $FILE | wc -l`; 
    killed=`grep 'TIME OUT' $FILE | wc -l`;
    strange_term=`grep 'Strange term' $FILE | wc -l`;
    r_total=`grep 'cmd = perl ' $FILE | wc -l`;
    total=$((inequivalent+adaptors+killed+missing));
    r_total=$((r_total_minus+r_total_plus));
    echo -e $i '\t' $inequivalent '(' $strange_term ')\t' $adaptors '\t' $killed '\t' $missing '\t\t' $total '(' $r_total ')'; 
    g_inequivalent=$((g_inequivalent+inequivalent));
    g_adaptors=$((g_adaptors+adaptors));
    g_missing=$((g_missing+missing));
    g_killed=$((g_killed+killed));
    g_total=$((g_total+total));
    g_strange_term=$((g_strange_term+strange_term));
done
echo -e  'Total\t' $g_inequivalent '(' $g_strange_term ')\t' $g_adaptors '\t' $g_killed '\t' $g_missing '\t\t' $g_total; 
