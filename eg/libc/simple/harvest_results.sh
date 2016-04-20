#!/bin/sh
g_inequivalent=0;
g_adaptors=0;
g_missing=0;
g_killed=0;
g_total=0;
g_strange_term=0;
suffix="";
echo -e '#\tIneq\t\t#adpt\tTimeout\tf1_crash\ttotal';
if [ "$1" == "-0" ] ; then
    suffix="-zero";
elif [ "$1" == "-1" ] ; then 
    suffix="-identity";
fi
for i in {1..8}; do 
    inequivalent=`grep 'not equivalent' ../simple-$i/$i$suffix.txt | wc -l`; 
    adaptors=`grep 'Final adaptor' ../simple-$i/$i$suffix.txt | wc -l`; 
    missing=`grep 'Missing results' ../simple-$i/$i$suffix.txt | wc -l`; 
    killed=`grep 'killed by alarm' ../simple-$i/$i$suffix.txt | wc -l`;
    strange_term=`grep 'Strange term' ../simple-$i/$i$suffix.txt | wc -l`;
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
