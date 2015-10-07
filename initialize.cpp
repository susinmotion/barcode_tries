#include "trie.h"
#include <string>
#include <fstream>
extern int BARCODE_LENGTH;

int ** initializeHashMtx(){
    int ** ppHashMatrixPointer = new int*[400];
    short int count;
    for (int row = 0; row < 400; row++){
        ppHashMatrixPointer[row]=new int[5];
        for (int col = 0; col < 5; col++){
            *(* (ppHashMatrixPointer+row)+col) = count;
            count++;
        }
    }
    return ppHashMatrixPointer;
}
void readFileIntoTrie(Trie* trie){
//    string filename = "/mnt/storage/data/justin/Archive/miseq/Data/Intensities/BaseCalls/1_S1_L001_R1_001.fastq";
    string filename = "veryshort2.txt";
    cout<<"in read file"<<filename<<endl;
    int count=0;
    ifstream readfile (filename.c_str());
    string alignSequenceStart="GTTCTTCGG";
    string alignSequenceFinish="GGGGG";
    string sequence;
    string barcode;
    string target="AAAA";
    string throwoutstring;
    int indexOfAlignStart;
    int indexOfAlignFinish;

    int ** ppHashMatrixPointer = initializeHashMtx();
    if (readfile.is_open()){
        cout<<"file isopen"<<endl;
        while (getline(readfile,throwoutstring)){
            count++;
            readfile>>sequence;
            indexOfAlignStart=sequence.find(alignSequenceStart,BARCODE_LENGTH);
            indexOfAlignFinish=sequence.find(alignSequenceFinish,BARCODE_LENGTH+alignSequenceStart.length());
            if ((indexOfAlignStart == -1) || (indexOfAlignFinish == -1) ){
                readfile>>throwoutstring;
                getline(readfile,throwoutstring);
                getline(readfile,throwoutstring);
                continue;
            }
            barcode=sequence.substr(indexOfAlignStart-BARCODE_LENGTH, BARCODE_LENGTH);
            sequence=sequence.substr(BARCODE_LENGTH+alignSequenceStart.length(), indexOfAlignFinish-BARCODE_LENGTH-alignSequenceStart.length());
            trie->addBarcode(barcode,sequence, target, ppHashMatrixPointer);
            readfile>>throwoutstring;
            getline(readfile, throwoutstring);
            getline(readfile,throwoutstring);
        }
    }
}
