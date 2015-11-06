#!/bin/bash

source config.cfg
echo $FILENAME
arr=$(echo $FILENAME | tr "," "\n")
#cat $FILENAME1 $FILENAME2 > allfiles.gz
echo ${arr[*]}
gzcat ${arr[*]} | ./secondtrie


