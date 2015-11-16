#!/bin/bash

head -n 3 example.cfg>tmp.cfg
source tmp.cfg
echo $FILENAMES
arr=$(echo $FILENAMES | tr "," "\n")
echo ${arr[*]}
mkdir $OUTPUTFILENAME
if [ "$ZIPPED" = "yes" ]
	then
	echo $ZIPPED
	zcat ${arr[*]} | ./secondtrie

else
        cat ${arr[*]} | ./secondtrie
fi
rm tmp.cfg
