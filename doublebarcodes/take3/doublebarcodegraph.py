import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as colors
import cPickle as pickle

MAX_FAMILY_SIZE=83
usedPrimaryBarcodes=22747
#primaryBarcodes=0
#secondaryBarcodeCounts=[ [] for _ in xrange(MAX_FAMILY_SIZE) ]#each list is a secondary barcode, each index is a primary barcode
#with open("summarySHORT.txt", 'r') as f:
#	stillWorking=True
#	line=f.next().split()
#	while stillWorking==True:
#		if len(line)==4:
#			primaryBarcodes+=1
#			tempSecondaryBarcodeCounts=[ 0 for _ in xrange(MAX_FAMILY_SIZE)]
#			for i in range(len(secondaryBarcodeCounts)):
#				try:
#					line=f.next().split()
#					if len(line)==2:
#						count=int(line[1])
#						if count > 1:
#							tempSecondaryBarcodeCounts[i]=count
#					else:
#						break
#				except Exception as e:
#					print e
#					print "exception!"
#					stillWorking=False
#					break
#
#			tempSecondaryBarcodeCounts.sort(reverse=True)
#			for j in range(MAX_FAMILY_SIZE):
#				secondaryBarcodeCounts[j].append(tempSecondaryBarcodeCounts[j])
#
#print primaryBarcodes, " number of primary barcodes"
#usedPrimaryBarcodes=len(secondaryBarcodeCounts[0])
#print usedPrimaryBarcodes, " number of primary barcodes in array"


#pickle.dump( secondaryBarcodeCounts, open( "secondaryBarcodeCountsShort.p", "wb" ) )


secondaryBarcodeCounts=pickle.load(open("secondaryBarcodeCounts.p","rb"))
keys=[]
for i in range(usedPrimaryBarcodes):
	keys.append(sum(index[i] for index in secondaryBarcodeCounts))
print "made keys"
pickle.dump(keys, open("keys.p", "wb"))
#keys=pickle.load(open("keys.p","rb"))
inds=np.array(keys).argsort()
print "made inds"
data=np.array([np.array(index)[inds] for index in secondaryBarcodeCounts])
print "yo"

colorslist=["r","orchid","gold","mediumspringgreen","c","blue", "lavenderblush","darkmagenta","lightskyblue", "blueviolet","plum","dodgerblue","yellow","hotpink","orange"]
	#make this into a numpy array. sort by sum, keys situation

y_offset=np.array([0.0]*usedPrimaryBarcodes)

for i in range(MAX_FAMILY_SIZE):
	print i
	plt.bar( (np.arange(usedPrimaryBarcodes)), data[i], color=colorslist[i%14], bottom=y_offset)
	y_offset=y_offset+ data[i]

colors = colors[::-1]
print "Yo"

#plt.show()
plt.savefig("")
#graph the thing


