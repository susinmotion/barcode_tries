#ABOUT:
This software takes in barcoded fastq files and outputs the number of reads reflecting each varaint.

##TO USE:
Download the file and unarchive as you choose. All contents can be found at github.com/susinmotion/barcode_tries. An easy-to-read version of this document can also be found at that URL.

##SETTING CONGIFURATIONS:
Open config.cfg in the text editor of your choice. Edit the existing text to reflect the names of genes of interest, barcode length, target sequences, etc. Use a comma (,-no spaces) to separate multiple entries for a given variable. Note the equals sign after ZIPPED and FILENAMES--do not delete it.
A detailed description of the configuration variables follows in "Config File Details."

##RUNNING THE PROGRAM:
In your terminal (cmd for windows), type `make` and press enter.<br>
If this does not yield errors, you're good to go.<br>
Type `./shell.sh >output.txt&` and press enter. <br>
A debug file will be saved to "output.txt". The end of this file will say "I'm done" when the program has finished running<br>
The process could take between 15 minutes and 12 hours, depending on the memory of your computer and the size of the files.

##RESULTS:
An output file will be created for each ROI(Gene) and Phase listed, named [GENE]_[PHASE].txt and including a list of variants and counts for a given ROI/Phase.
~~In addition, users can opt to output a file named "summary.txt" containing variants for each barcode for all ROI/phase combinations by setting OUTPUT_SUMMARY_FILE TRUE in the config file. This file is HUGE and will take up valuable memory. Setting this parameter is not recommended.~~

##UNDERSTANDING THE CONFIG FILE:
Below is an explanation of each of the variables in config.cfg. Multiple parameters are comma delimited (first_parameter,second_parameter)--no white space--and should be listed in a consistent order across parameters. If multiple ROIs share the same parameters, they still must be listed twice. For example, for two ROIs with a forward alignment sequence of AAA `FORWARD_ALIGN_SEQ AAA,AAA`<br>

`ZIPPED=yes`<br>
Type yes (all lower case) if input files are zipped, no if they are not zipped.

`FILENAMES=example.tar.gz,example2.txt.gz`<br>
List of input files. All files for a given run must either be zipped or unzipped. Each file must be zipped separately, but the program can tolerate a number of zipped formats. Note the equals sign following FILENAMES. Do not delete it! No white space.

`GENES gene1,gene2`<br>
Names of the genes of interest, used for labeling output files. 

`BARCODE_LENGTH 4`<br>
Length of a barcode

`FORWARD_ALIGN_SEQ GTTCTTCGG,AGCTTTA`<br>
`REVERSE_ALIGN_SEQ GGGGG,TACT`<br>
`TARGET AAAA,TGACTTAG`<br>
Forward and reverse align sequences, and target sequences, corresponding to the gene names. The program handles reverse complements, so no need to list these separately. Targets should not include the alignment sequences. 

`THRESHOLD_OF_IMPORTANCE 3`<br>
How many reads of the same barcode constitutes a trial. Reads that don't meet this threshold will be excluded from analyses. The recommended lower limit for this value is 3.


`MAX_PHASE 5`<br>
The greatest number of bases preceding the barcode. For example, if you have reads with 0, 2, 6, and 7 bases preceding the barcode, put 7 here.

`PHASE_SHIFTS_REV_TO_FORWARD 0:1|1:2|2:0,1:0` <br>
If the phases from reverse complement reads do not correspond directly to those in forward reads, phase shifts may be listed here. The phase found in the reverse complement is listed first, then its corresponding phase in the forward read. Phase shifts for a given ROI are separated by |. Phase shift sets for different ROIs are comma delimited, as with other parameters.

##UNDERSTANDING YOUR RESULTS:
Three sets of files will be output:
~~* summary_IMPORTANT.txt~~
* [GENE]_[PHASE].txt, for each gene/phase combination
* [GENE]_[PHASE]matrix.txt, for each gene/phase combination

~~**summary_IMPORTANT.txt** includes a list of all barcodes that met the threshold of importance, any variants found, and the number of times they were encountered for each phase/gene combination.~~

**[GENE]_[PHASE].txt files** contain the name of the gene, the phase number, the number of barcodes with sufficient reads in this ROI/phase (this threshold is user set in "config.cfg"), the total number of variants found, and a list of variants.
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

**[GENE]_[PHASE]matrix.txt files** contain 5 rows and n columns, where n is the length of the target sequence. Each row indicates a base (A,C,G,T,N) and each column indicates a position in the the target sequence, so a row/column pair represents a particular substitution. Numbers in each position in the matrix represent the proportion (of the total number of substitutions for that gene/phase combo) that that substitution was found.


