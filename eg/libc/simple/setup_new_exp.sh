#!/bin/bash

<<<<<<< Updated upstream
bkp_num=6;
dest_dir=identity;
synth_suffix=-identity;
=======
# bkp_num=1;
# dest_dir=identity;
# synth_suffix=-identity;
>>>>>>> Stashed changes

bkp_num=0;
toplevel_synth_suffix=;
interim_synth_suffix=one;
dest_dir=simple;

#bkp_num=3;
#toplevel_synth_suffix=typeconv-top;
#interim_synth_suffix=typeconv;
#dest_dir=typeconv;

for i in {1..8};
do
    rm -rf ../$dest_dir-$i/fuzzball-tmp-*;
    mkdir ../$dest_dir-$i/bkp-$bkp_num;
    mv ../$dest_dir-$i/status ../$dest_dir-$i/bkp-$bkp_num/;
    echo "nothing to bkp, previous simple adaptor runs in typeconv-$i/bkp-0 to 3" > ../$dest_dir-$i/bkp-$bkp_num/finish_status;
    echo "Running simple adaptor with fixes in SRFM#decide_wd, #query_maxval, #region_for and FM#compare_conc_se" > ../$dest_dir-$i/status;
    cp ../$dest_dir-$i/$i.txt ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.pl ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/two-funcs ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.lst ../$dest_dir-$i/bkp-$bkp_num/;
    cp ../$dest_dir-$i/*.txt ../$dest_dir-$i/bkp-$bkp_num/;
    
    cp ../simple/synth$toplevel_synth_suffix.pl ../$dest_dir-$i/;
    cp ../simple/synth-$interim_synth_suffix.pl ../$dest_dir-$i/;
    cp ../simple/two-funcs ../$dest_dir-$i/;
    cp ../simple/types-no-float-1204.lst ../$dest_dir-$i/;
done;
