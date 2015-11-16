#!/bin/bash

head -n 2 configforveryshort5.cfg>tmp.cfg
source tmp.cfg
arr=$(echo $FILENAMES | tr "," "\n")
echo ${arr[*]}
if [ "$ZIPPED" = "yes" ]
	then
	zcat ${arr[*]} | ./secondtrie

else
        cat ${arr[*]} | ./secondtrie
fi
rm tmp.cfg
