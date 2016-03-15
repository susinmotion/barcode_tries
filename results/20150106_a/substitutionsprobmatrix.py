import pandas as pd
import numpy as np
from matplotlib.ticker import LogFormatter
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm
import matplotlib.cm as cm
from itertools import product
from itertools import permutations
import os
def fourbyfour(filenames, target):
    df = pd.DataFrame(np.array([[0]*4] * 4), index=list('ACGT'), columns=list('ACGT'))
    returnMtx=[[0 for x in range(4)] for x in range(4)]
    count=0
    baseDict={'A':0, 'C':1,'G':2,'T':3}
    for f in filenames:
        with open(f, 'r') as ff:
            read_data = ff.readlines()
            nodesChecked=read_data[3].split()[3]
            for line in read_data[4:-1]:
                position = int(line.split()[0])
                targetBase=target[position]
                targetBaseNo=baseDict[targetBase]

                base = line.split()[1]
                baseNo=baseDict[base]

                timesFound = int(line.split()[2])
                count=count+ timesFound
                df[targetBase][base]=df[targetBase][base]+timesFound
                returnMtx[baseNo][targetBaseNo]=returnMtx[baseNo][targetBaseNo]+timesFound

    print returnMtx, nodesChecked
    print df
    df.to_csv("fourbyfour.csv")
    returnMtx.to_csv("fourbyfourmatrix.csv")
    return returnMtx

def sixtyfourbyfour(filenames, target):
    bases=['A','C','G','T']
    trios= ["".join(p) for p in product(bases, repeat=3)]

    thresholds=['3','5','7','9']
    phases=[0,1,2,3,4,5,6,7,8,9]
    counts=pd.DataFrame(np.array([[None]*10]*4),index=thresholds,columns=phases)
    raw_counts=pd.DataFrame(np.array([[None]*10]*4),index=thresholds,columns=phases)
    for f in filenames:
        threshold=f.split(".")[0][-1]
        #print threshold
        gene=f.split("_")[0]
        df = pd.DataFrame(np.array([[0]*64] * 4), index=bases, columns=trios)
        with open(f, 'r') as ff:
            count=0
            variants_found=0
            read_data = ff.readlines()
            #print read_data[:5]
            nodesChecked=int(read_data[2].split()[3])
            phase=int(read_data[1].split()[1])
            for line in read_data[4:-1]:
                position = int(line.split()[0])
                timesFound = int(line.split()[2])
                base = line.split()[1]
                if base =='A':
                    if (position>0 and position<len(target)-1):
                        #find the base that's getting changed
                        targetBase=target[position]
                        	#if (not (base=='A' and targetBase=='C') and not(base =='T' and targetBase=='G') and not (base=='T' and targetBase=='C') and not (base=='A' and targetBase=='G')):
                                #find the bases around it
                     	if targetBase=='C':
                                count=count+timesFound
                                trio=target[position-1:position+2]
                                #hash it, basically
                                print trio, targetBase, "->", base
                                trioNumber=trios.index(trio)
                                baseNo=bases.index(base)
                                #variants_found=variants_found+timesFound
                                df[trio][base]=df[trio][base]+timesFound
                                if base==targetBase:
                                        print line
        counts[phase][threshold]=float(count)/nodesChecked
        raw_counts[phase][threshold]=float(count)
        #print count, phase, threshold
        #print nodesChecked
        #print counts[phase][threshold]
        df=df.divide(nodesChecked)
        #print df
        for trio in trios:
            if not trio in target:
                for base in bases:
                    df[trio][base]="NA"
        #df.to_pickle(gene+"/CAOnly/"+f+"64matrix.pkl")
        #df.to_csv(gene+"/CAOnly/"+f+"64matrix.csv")
        print df
    #print counts
    #print raw_counts
    counts.to_pickle(gene+"/CAOnly/"+gene+"countsbyphase.pkl")
    counts.to_csv(gene+"/CAOnly/"+gene+"countsbyphase.csv")
    raw_counts.to_csv(gene+"/CAOnly/"+gene+"rawcountsbyphase.csv")
    raw_counts.to_pickle(gene+"/CAOnly/"+gene+"rawcountsbyphase.pkl")
    #countsplot=counts.plot().get_figure()
    #countsplot.savefig(gene+"/ExclCA_GT_CT_GA/"+gene+"countsplot.png")
    #rawcountsplot=raw_counts.plot().get_figure()
    #rawcountsplot.savefig(gene+"/"+gene+"rawcountsplot.png")

def heatmap(filenames, target):
    print "hello"
    bases=['A','C','G','T']
    shifts=list(permutations(bases,2))
    print shifts
    dfs=[None]*len(shifts)
    count=0
    maxval=0
    minval=1
    for shift in shifts:
        dfs[count] = pd.DataFrame(np.array([[0.0]*4]*4), index=bases, columns=bases)
        nodesChecked=0
        for f in filenames:
            threshold=f.split(".")[0][-1]
            #print threshold
            gene=f.split("_")[0]
            with open(f, 'r') as ff:
                variants_found=0
                read_data = ff.readlines()
                nodesChecked=nodesChecked+float(read_data[2].split()[3])
                phase=int(read_data[1].split()[1])
                for line in read_data[4:-1]:
                    position = int(line.split()[0])
                    timesFound = float(line.split()[2])
                    base = line.split()[1]
                    if base == shift[1]:
                        if (position>0 and position<len(target)-1):
                            #find the base that's getting changed
                            targetBase=target[position]
                            if targetBase==shift[0]:
                                    #find the bases around it
                                    before=target[position-1]
                                    after=target[position+1]

                                    baseNo=bases.index(base)
                                    dfs[count][before][after]=dfs[count][before][after]+timesFound

        dfs[count]=dfs[count].divide(nodesChecked)
        if dfs[count].values.max() > maxval:
            maxval=dfs[count].values.max()
        print maxval, " max"
        try:
            if dfs[count].values[dfs[count].values.nonzero()].min()< minval:
                minval=dfs[count].values[dfs[count].values.nonzero()].min()
        except Exception as e:
            print e
        print minval, " min"

        for base1 in bases:
            for base2 in bases:
                if not (base1+shift[0]+base2) in target:
                    dfs[count][base1][base2]=10

        print dfs[count]
	print type(dfs[count])
        dfs[count]=np.log(dfs[count])
        print dfs[count]
        print shift
        #print type(dfs[count])
	dfs[count][dfs[count]==-np.inf]=-20
        print dfs[count]
        dfs[count].to_pickle(shifts[count][0]+"->"+shifts[count][1]+"pkl")
        dfs[count]=np.ma.masked_array(dfs[count],mask=dfs[count]>1)
        print dfs[count]
	count=count+1
    count2=0
    for df in dfs:
	print df
        minval= 8.53156932331e-08
        maxval= 0.000463861424108
	fig,ax=plt.subplots()
        ax.set_axis_bgcolor('black')
        ax.invert_yaxis()
        ax.xaxis.tick_top()
        ax.set_xticks(np.arange(df.shape[0])+0.5, minor=False)
        ax.set_yticks(np.arange(df.shape[1])+0.5, minor=False)
        ax.set_xticklabels(list('ACGT'), minor=False)
        ax.set_yticklabels(list('ACGT'), minor=False)
        




	heatmap = plt.pcolor(df, cmap=cm.Blues, vmin=-20, vmax=np.log(maxval))
        print "hi"
        #fig, ax = plt.subplots()
        #ax.set_axis_bgcolor('black')
        # put the major ticks at the middle of each cell
        #ax.set_xticks(np.arange(df.shape[0])+0.5, minor=False)
        #ax.set_yticks(np.arange(df.shape[1])+0.5, minor=False)
	'''
        # want a more natural, table-like display
        ax.invert_yaxis()
        ax.xaxis.tick_top()
        ax.set_xticklabels(list('ACGT'), minor=False)
        ax.set_yticklabels(list('ACGT'), minor=False)
        #plt.show()'''
	l_f = LogFormatter(10, labelOnlyBase=False)
	cbar=fig.colorbar(heatmap, ticks=np.logspace(minval, maxval), format=l_f, orientation='horizontal')
	plt.show()
        plt.savefig(shifts[count2][0]+"->"+shifts[count2][1]+"fig")
        #heatmap=df.plot().get_figure()    
        count2=count2+1
#sixtyfourbyfour(["rpoB_0_thresh3.txt","rpoB_0_thresh5.txt","rpoB_0_thresh7.txt","rpoB_0_thresh9.txt","rpoB_1_thresh3.txt","rpoB_1_thresh5.txt","rpoB_1_thresh7.txt","rpoB_1_thresh9.txt","rpoB_2_thresh3.txt","rpoB_2_thresh5.txt","rpoB_2_thresh7.txt","rpoB_2_thresh9.txt","rpoB_3_thresh3.txt","rpoB_3_thresh5.txt","rpoB_3_thresh7.txt","rpoB_3_thresh9.txt","rpoB_4_thresh3.txt","rpoB_4_thresh5.txt","rpoB_4_thresh7.txt","rpoB_4_thresh9.txt","rpoB_5_thresh3.txt","rpoB_5_thresh5.txt","rpoB_5_thresh7.txt","rpoB_5_thresh9.txt","rpoB_6_thresh3.txt","rpoB_6_thresh5.txt","rpoB_6_thresh7.txt","rpoB_6_thresh9.txt","rpoB_7_thresh3.txt","rpoB_7_thresh5.txt","rpoB_7_thresh7.txt","rpoB_7_thresh9.txt","rpoB_8_thresh3.txt","rpoB_8_thresh5.txt","rpoB_8_thresh7.txt","rpoB_8_thresh9.txt","rpoB_9_thresh3.txt","rpoB_9_thresh5.txt","rpoB_9_thresh7.txt","rpoB_9_thresh9.txt"], "TGTCTCAGTTTATGGACCAGAACAACCCGCTGTCTGAGATTACGCACAAACGTCGTATCTCCGCACTCGGCCCAGGCGGTCT")
#sixtyfourbyfour(["mrcA_0_thresh3.txt","mrcA_0_thresh5.txt","mrcA_0_thresh7.txt","mrcA_0_thresh9.txt","mrcA_1_thresh3.txt","mrcA_1_thresh5.txt","mrcA_1_thresh7.txt","mrcA_1_thresh9.txt","mrcA_2_thresh3.txt","mrcA_2_thresh5.txt","mrcA_2_thresh7.txt","mrcA_2_thresh9.txt","mrcA_3_thresh3.txt","mrcA_3_thresh5.txt","mrcA_3_thresh7.txt","mrcA_3_thresh9.txt","mrcA_4_thresh3.txt","mrcA_4_thresh5.txt","mrcA_4_thresh7.txt","mrcA_4_thresh9.txt","mrcA_5_thresh3.txt","mrcA_5_thresh5.txt","mrcA_5_thresh7.txt","mrcA_5_thresh9.txt","mrcA_6_thresh3.txt","mrcA_6_thresh5.txt","mrcA_6_thresh7.txt","mrcA_6_thresh9.txt","mrcA_7_thresh3.txt","mrcA_7_thresh5.txt","mrcA_7_thresh7.txt","mrcA_7_thresh9.txt","mrcA_8_thresh3.txt","mrcA_8_thresh5.txt","mrcA_8_thresh7.txt","mrcA_8_thresh9.txt","mrcA_9_thresh3.txt","mrcA_9_thresh5.txt","mrcA_9_thresh7.txt","mrcA_9_thresh9.txt"], "GTGAACTCGGCGCTGGTGTCGATCAATCCGCAAAACGGTGCCGTTATGGCGCTGGTCGGTGGCTTTGATTTCAATCAGAGCAAGTTTAACC")
#sixtyfourbyfour(["cspe_0_thresh3.txt","cspe_0_thresh5.txt","cspe_0_thresh7.txt","cspe_0_thresh9.txt","cspe_1_thresh3.txt","cspe_1_thresh5.txt","cspe_1_thresh7.txt","cspe_1_thresh9.txt","cspe_2_thresh3.txt","cspe_2_thresh5.txt","cspe_2_thresh7.txt","cspe_2_thresh9.txt","cspe_3_thresh3.txt","cspe_3_thresh5.txt","cspe_3_thresh7.txt","cspe_3_thresh9.txt","cspe_4_thresh3.txt","cspe_4_thresh5.txt","cspe_4_thresh7.txt","cspe_4_thresh9.txt"], "GCCCTTCTGCTGCAAACGTAATCGCTCTGTAAGATACGTCAGCAAGAATTCAAAACCCGCTTAATCAGCGGGTTTTTTTTGGTCTTTAGTGTGC")
#sixtyfourbyfour(["rpob_utr_0_thresh3.txt","rpob_utr_0_thresh5.txt","rpob_utr_0_thresh7.txt","rpob_utr_0_thresh9.txt","rpob_utr_1_thresh3.txt","rpob_utr_1_thresh5.txt","rpob_utr_1_thresh7.txt","rpob_utr_1_thresh9.txt","rpob_utr_2_thresh3.txt","rpob_utr_2_thresh5.txt","rpob_utr_2_thresh7.txt","rpob_utr_2_thresh9.txt","rpob_utr_3_thresh3.txt","rpob_utr_3_thresh5.txt","rpob_utr_3_thresh7.txt","rpob_utr_3_thresh9.txt","rpob_utr_4_thresh3.txt","rpob_utr_4_thresh5.txt","rpob_utr_4_thresh7.txt","rpob_utr_4_thresh9.txt"], "GAAGACGAGTAATTCTCGCTCAAACAGGTCACTGCTGTCGGGTTAAAACCCGGCAGCGGATTGTGCTAACTCCGACGGGAGCAAATCCGTG")

#sixtyfourbyfour(["rpoz_0_thresh5.txt","rpoz_1_thresh5.txt","rpoz_2_thresh5.txt","rpoz_3_thresh5.txt","rpoz_4_thresh5.txt"],"ACCTGTGGAGCTTTTTAAGTATGGCACGCGTAACTGTTCAGGACGCTGTAGAGAAAATTGGTAACCGTTTTGACCTGGTACTGGTCGCC")
heatmap(["rpoB_0_thresh5.txt","rpoB_1_thresh5.txt","rpoB_2_thresh5.txt","rpoB_3_thresh5.txt","rpoB_4_thresh5.txt"],"ACCTGTGGAGCTTTTTAAGTATGGCACGCGTAACTGTTCAGGACGCTGTAGAGAAAATTGGTAACCGTTTTGACCTGGTACTGGTCGCC")           
#heatmap(["rpob_utr_0_thresh5.txt","rpob_utr_1_thresh5.txt","rpob_utr_2_thresh5.txt","rpob_utr_3_thresh5.txt","rpob_utr_4_thresh5.txt"],"GAAGACGAGTAATTCTCGCTCAAACAGGTCACTGCTGTCGGGTTAAAACCCGGCAGCGGATTGTGCTAACTCCGACGGGAGCAAATCCGTG")
#heatmap(["cspe_0_thresh5.txt","cspe_1_thresh5.txt","cspe_2_thresh5.txt","cspe_3_thresh5.txt","cspe_4_thresh5.txt"],"GCCCTTCTGCTGCAAACGTAATCGCTCTGTAAGATACGTCAGCAAGAATTCAAAACCCGCTTAATCAGCGGGTTTTTTTTGGTCTTTAGTGTGC")                                                                                      

