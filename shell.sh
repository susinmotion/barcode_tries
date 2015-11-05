#!/bin/bash

source config.cfg
echo $FILENAME1
cat $FILENAME1 $FILENAME2 > allfiles.gz
gzcat $FILENAME1 | ./secondtrie