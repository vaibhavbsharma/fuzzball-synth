#!/bin/sh

kill_flag=0;
print_flag=0;
if [ "$1" == "-kill" ] ; then
    kill_flag=1;
fi
if [ "$1" == "-print" ] ; then
    print_flag=1;
fi
for pid in `ps -aef | grep -i fuzzball | grep -i vaibhav | tr -s ' ' | cut -d ' ' -f 2`; do 
    ppid=`ps -aef | grep -i fuzzball | grep -i vaibhav | grep $pid | grep -v "grep" | grep -v "SMTLIB2" | tr -s ' ' | cut -d ' ' -f 3`;  
    if [ $print_flag -eq 1 ] ; 
    then
	echo $pid "ppid = " $ppid;
    fi;
    if [ $ppid -eq 1 ] ; 
    then 
	echo $pid $ppid;
	if [ $kill_flag -eq 1 ] ; 
	then
	    kill -9 $pid;
	fi;
    fi; 
done
