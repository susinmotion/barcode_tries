#!/bin/bash

head -n 2 config.cfg>tmp.cfg
source tmp.cfg
echo $FILENAMES
arr=$(echo $FILENAMES | tr "," "\n")
echo ${arr[*]}
if [ "$ZIPPED" = "yes" ]
	then
	echo $ZIPPED
	zcat ${arr[*]} | ./secondtrie

else
        cat ${arr[*]} | ./secondtrie
fi
rm tmp.cfg
