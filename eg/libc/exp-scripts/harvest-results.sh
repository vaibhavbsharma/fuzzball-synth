#!/bin/sh

if [[ $# -ne 4 ]]; then
    echo -e "$0: usage: harvest-results.sh <argument 1> <argument 2> <argument 3> <argument 4> <argument 5>"
    echo "arguments list is as follows";
    echo "1. <adapter family, 1=argsub, 2=typeconv, 3=arithmetic-int, 4=memsub>";
    echo "2. <log file to search through, e.g. 1.log>";
    echo "3. <prefix directory containing the argsub/typeconv/arith subdirectories, e.g. /export/scratch/vaibhav/glibc-exps>";
    echo "4. <number of bucket directories expected in prefix-directory/argsub or typeconv or arith/, e.g. 32>";
    
    exit 1
fi

ADAPTER_FAMILY=$1
LOGFILE=$2
PREFIX_DIR=$3
num_dirs=$4;

g_inequivalent=0;
g_adapters=0;
g_missing=0;
g_killed=0;
g_total=0;
g_strange_term=0;
suffix="";
echo -e '#\tIneq\t\t#adpt\tTimeout\tf1_crash\ttotal';
if [[ $ADAPTER_FAMILY -eq 4 ]]; then
    export SUBDIR="memsub";
elif [[ $ADAPTER_FAMILY -eq 3 ]]; then
    export SUBDIR="arith";
elif [[ $ADAPTER_FAMILY -eq 2 ]]; then
    export SUBDIR="typeconv";
else
    export SUBDIR="argsub";
fi

for ((i=1; i<=num_dirs; i++)); do
    FILE=$PREFIX_DIR/$SUBDIR/glibc-$i/logs/$LOGFILE
    inequivalent=`grep 'not equivalent' $FILE | wc -l`; 
    adapters=`grep 'Final adaptor' $FILE | wc -l`; 
    missing=`egrep -e 'Missing results|found ce fail' $FILE | wc -l`; 
    killed=`grep 'found timeout' $FILE | wc -l`;
    strange_term=`grep 'Strange term' $FILE | wc -l`;
    r_total=`grep 'cmd = perl ' $FILE | wc -l`;
    total=$((inequivalent+adapters+killed+missing));
    r_total=$((r_total_minus+r_total_plus));
    echo -e $i '\t' $inequivalent '(' $strange_term ')\t' $adapters '\t' $killed '\t' $missing '\t\t' $total '(' $r_total ')'; 
    g_inequivalent=$((g_inequivalent+inequivalent));
    g_adapters=$((g_adapters+adapters));
    g_missing=$((g_missing+missing));
    g_killed=$((g_killed+killed));
    g_total=$((g_total+total));
    g_strange_term=$((g_strange_term+strange_term));
done
echo -e  'Total\t' $g_inequivalent '(' $g_strange_term ')\t' $g_adapters '\t' $g_killed '\t' $g_missing '\t\t' $g_total; 
