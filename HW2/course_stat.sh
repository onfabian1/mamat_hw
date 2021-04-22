#!/bin/bash

#check valid num of args

if [ 1 != $# ]
then 
	echo "Wrong number of arguments" >&2
	exit 
fi

#check xxxxxx.txt exsits

var=$(ls -a | grep $1.txt)
if [[ $var == '' ]] 
then
	echo "Course Not Found" >&2
	exit
fi

#check folder xxxxxx_stat

var=$(ls -a | grep $1_stat)
if [[ $var != '' ]]
then
	rm -r $1_stat
fi
mkdir $1_stat

#writing to grades.txt

cat $1.txt | tail -n +2 | awk '{print $2}' > $1_stat/grades.txt
gcc -g -Wall calc_statistics.c -o prog.exe
./prog.exe ./$1_stat

