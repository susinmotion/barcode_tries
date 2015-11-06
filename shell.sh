#!/bin/bash

head -n 1 config.cfg>tmp.cfg
source tmp.cfg
echo $FILENAMES
arr=$(echo $FILENAMES | tr "," "\n")
echo ${arr[*]}
gzcat ${arr[*]} | ./secondtrie
rm tmp.cfg
