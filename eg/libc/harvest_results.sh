#!/bin/sh
g_inequivalent=0;
g_adaptors=0;
g_missing=0;
g_killed=0;
g_total=0;
g_strange_term=0;
suffix="";
num_dirs=0;
echo -e '#\tIneq\t\t#adpt\tTimeout\tf1_crash\ttotal';
if [ "$1" == "-arithmetic" ] ; then
    prefix_dir="arithmetic";
    num_dirs=8;
elif [ "$1" == "-simple" ] ; then 
    prefix_dir="simple";
    num_dirs=8;
elif [ "$1" == "-identity" ] ; then 
    prefix_dir="identity";
    num_dirs=2;
fi

bkp_dir="";
if [ $# -eq 3 ]; then
    if [ "$2" == "-bkp" ]; then
	bkp_dir="/bkp-$3/";
    fi
fi

for ((i=1; i<=num_dirs; i++)); do 
    inequivalent=`grep 'not equivalent' $prefix_dir-$i/$bkp_dir$i.txt | wc -l`; 
    adaptors=`grep 'Final adaptor' $prefix_dir-$i/$bkp_dir$i.txt | wc -l`; 
    missing=`grep 'Missing results' $prefix_dir-$i/$bkp_dir$i.txt | wc -l`; 
    killed=`grep 'killed by alarm' $prefix_dir-$i/$bkp_dir$i.txt | wc -l`;
    strange_term=`grep 'Strange term' $prefix_dir-$i/$bkp_dir$i.txt | wc -l`;
    total=$((inequivalent+adaptors+killed+missing));
    echo -e $i '\t' $inequivalent '(' $strange_term ')\t' $adaptors '\t' $killed '\t' $missing '\t\t' $total; 
    g_inequivalent=$((g_inequivalent+inequivalent));
    g_adaptors=$((g_adaptors+adaptors));
    g_missing=$((g_missing+missing));
    g_killed=$((g_killed+killed));
    g_total=$((g_total+total));
    g_strange_term=$((g_strange_term+strange_term));
done
echo -e  'Total\t' $g_inequivalent '(' $g_strange_term ')\t' $g_adaptors '\t' $g_killed '\t' $g_missing '\t\t' $g_total; 
