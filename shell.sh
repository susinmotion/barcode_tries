#!/bin/bash

head -n 2 config.cfg>tmp.cfg
source tmp.cfg
echo $FILENAMES
arr=$(echo $FILENAMES | tr "," "\n")
echo ${arr[*]}
if [ "$ZIPPED" = "yes" ]
	then
	echo $ZIPPED
	gzcat ${arr[*]} | ./secondtrie
fi
else
	${arr[*]} | ./secondtrie
rm tmp.cfg
