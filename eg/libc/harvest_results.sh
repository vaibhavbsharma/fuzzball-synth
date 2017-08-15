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
elif [ "$1" == "-typeconv" ] ; then 
    prefix_dir="typeconv";
    num_dirs=8;
fi

bkp_dir="logs";
if [ $# -eq 3 ]; then
    if [ "$2" == "-bkp" ]; then
	bkp_dir="/bkp-$3/";
    fi
fi

for ((i=1; i<=num_dirs; i++)); do 
    inequivalent_minus=`grep 'not equivalent' $prefix_dir-$i/${bkp_dir}/5.log | wc -l`; 
    inequivalent_plus=`grep 'not equivalent' $prefix_dir+$i/$bkp_dir/5.log | wc -l`; 
    adaptors_minus=`grep 'Final adaptor' $prefix_dir-$i/$bkp_dir/5.log | wc -l`; 
    adaptors_plus=`grep 'Final adaptor' $prefix_dir+$i/$bkp_dir/5.log | wc -l`; 
    missing_minus=`grep 'Missing results' $prefix_dir-$i/$bkp_dir/5.log | wc -l`; 
    missing_plus=`grep 'Missing results' $prefix_dir+$i/$bkp_dir/5.log | wc -l`; 
    killed_minus=`grep 'killed by alarm' $prefix_dir-$i/$bkp_dir/5.log | wc -l`;
    killed_plus=`grep 'killed by alarm' $prefix_dir+$i/$bkp_dir/5.log | wc -l`;
    strange_term_minus=`grep 'Strange term' $prefix_dir-$i/$bkp_dir/5.log | wc -l`;
    strange_term_plus=`grep 'Strange term' $prefix_dir-$i/$bkp_dir/5.log | wc -l`;
    r_total_minus=`grep 'Startin synth' $prefix_dir-$i/$bkp_dir/5.log | wc -l`;
    r_total_plus=`grep 'Startin synth' $prefix_dir+$i/$bkp_dir/5.log | wc -l`;
    inequivalent=$((inequivalent_minus+inequivalent_plus));
    adaptors=$((adaptors_minus+adaptors_plus));
    missing=$((missing_minus+missing_plus));
    killed=$((killed_minus+killed_plus));
    strange_term=$((strange_minus+strange_plus));
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
