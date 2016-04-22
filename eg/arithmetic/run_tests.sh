#! /bin/sh

timeStamp=`date +%Y-%m-%d-%H-%M-%S`
resultsDir="${timeStamp}_results"
echo "+ Creating results directory: $resultsDir"
mkdir -p $resultsDir

echo "+ Iterating over 9 different seeds"
for seed in `seq 0 9`;
do
    echo "   + Starting test with seed $seed..."
    start=`date +%s`
    ocaml synth.ml arithmetic int 3 1 1 ${seed} > ${resultsDir}/$seed.out
    end=`date +%s`
    totalTime=$((end-start))
    echo "Total time: $totalTime" >> ${resultsDir}/${seed}.out
    rm -rf fuzzball-tmp-*
done

echo "+ Combining result files in $resultsDir and storing them in All_Results.csv"
python parse_results.py $resultsDir All_Results.csv

echo "+ Done!"
