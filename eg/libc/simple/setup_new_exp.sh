#!/bin/bash

bkp_num=5;
dest_dir=identity;
synth_suffix=-identity;

#bkp_num=7;
#synth_suffix=;
#dest_dir=simple;

for i in {1..2};
do
    rm -rf ../$dest_dir-$i/fuzzball-tmp-*;
    mkdir ../$dest_dir-$i/bkp-$bkp_num;
    touch ../$dest_dir-$i/bkp-$bkp_num/status;
    echo "With broken symbolic state side-effect equivalence checking and broken query_condition, but with concretely-addressed memory side-effects equivalence checking, state snapshotting, region limit 936" > ../$dest_dir-$i/bkp-$bkp_num/status;
    cp ../$dest_dir-$i/$i.txt ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.pl ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/two-funcs ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.lst ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.txt ../$dest_dir-$i/bkp-$bkp_num/;
    
    #cp ../simple/synth-memcheck.pl ../$dest_dir-$i/;
    cp ../simple/synth$synth_suffix.pl ../$dest_dir-$i/;
    cp ../simple/synth-typeconv.pl ../$dest_dir-$i/;
    cp ../simple/two-funcs ../$dest_dir-$i/;
    cp ../simple/types-no-float-1204.lst ../$dest_dir-$i/;
    
    #cp ../simple/typeconv_adaptors_all_fnums.txt ../simple-$i/;
done;
