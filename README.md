#ABOUT:
This software takes in barcoded fastq files and outputs the number of reads reflecting each varaint.

##TO USE:
Download the file and unarchive as you choose. 

##SETTING CONGIFURATIONS:
Open the file config.cfg. Edit the existing text to reflect the names of genes of interest, barcode length, target sequences, etc. Use a comma (,-no spaces) to separate multiple entries for a given variable. Note the equals sign after FILENAMES.
A detailed description of the configuration variables follows in "Config File Details."

##RUNNING THE PROGRAM:
In your terminal (cmd for windows), type make and press enter.
If this does not yield errors, you're good to go.
Type ./shell.sh and press enter.

##RESULTS:
An output file will be created for each ROI(Gene) and Phase listed, named [GENE]_[PHASE].txt and including a list of variants and counts for a given ROI/Phase.
In addition, users can opt to output a file named "summary.txt" containing variants for each barcode for all ROI/phase combinations by setting OUTPUT_SUMMARY_FILE TRUE in the config file.

##UNDERSTANDING THE CONFIG FILE:
Below is an explanation of each of the variables in config.cfg. Multiple parameters are comma delimited (first_parameter,second_parameter)--no white space.

`FILENAMES=example.tar.gz,example2.txt.gz`<br>
List of input files, in zipped format. Each file must be zipped separately, but the program can tolerate a number of zipped formats. Note the equals sign following FILENAMES. Do not delete it! No white space.

`GENES gene1,gene2`<br>
Names of the genes of interest, used for labeling output files. 

`BARCODE_LENGTH 4`<br>
Length of a barcode

`FORWARD_ALIGN_SEQ GTTCTTCGG,AGCTTTA`<br>
`REVERSE_ALIGN_SEQ GGGGG,TACT`<br>
`TARGET AAAA,TGACTTAG`<br>
Forward and reverse align sequences, and target sequences, corresponding to the gene names. The program handles reverse complements, so no need to list these separately. 

`THRESHOLD_OF_IMPORTANCE 3`<br>
How many reads constitutes a trial. Reads that don't meet this threshold will be excluded from analyses. 

`MAX_PHASE 5`<br>
The greatest number of bases preceding the barcode. For example, if you have reads with 0, 2, 6, and 7 bases preceding the barcode, put 7 here.


##UNDERSTANDING YOUR RESULTS:
Output files for a given ROI/phase, named [GENE]_[PHASE].txt, contain the name of the gene, the phase number, the number of barcodes with sufficient reads in this ROI/phase (this threshold is user set in "config.cfg"), the total number of variants found, and a list of variants.
Substitutions are noted Position Base TimesFound
Indels are noted Position Length TimesFound. A negative length indicates a deletion; a positive length indicates an insertion.

example gene1_0.txt:
```
ROI: gene1
Phase: 0
Total nodes checked: 10
Total variants found: 4
1 G 46
1 N 1
2 N 1
2 1 1
2 -5 50
```
2 G 46 denotes that the third base (position 2, starting at 0) was replaced by G 46 times in the sample.
2 -5 50 denotes that a deletion of 5 base pairs starting at the 3rd base (position 2) was found 50 times in the sample. 


