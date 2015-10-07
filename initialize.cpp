#include "trie.h"
#include <string>
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
    string alignSequence="GTTCTTCGG";
    string sequence;
    string barcode;
    string target="GTTCTTCGGAAAA";
    string throwoutstring;
    int indexOfAlign;

    int ** ppHashMatrixPointer = initializeHashMtx();
    if (readfile.is_open()){
        cout<<"file isopen"<<endl;
        while (getline(readfile,throwoutstring)){
            count++;
            readfile>>sequence;
            indexOfAlign=sequence.find(alignSequence,BARCODE_LENGTH);
            if (indexOfAlign == -1){
                readfile>>throwoutstring;
                getline(readfile,throwoutstring);
                getline(readfile,throwoutstring);
                continue;
            }
            barcode=sequence.substr(indexOfAlign-BARCODE_LENGTH, BARCODE_LENGTH);
            trie->addBarcode(barcode,sequence.substr(BARCODE_LENGTH), target, ppHashMatrixPointer);
            readfile>>throwoutstring;
            getline(readfile, throwoutstring);
            getline(readfile,throwoutstring);
        }
    }
}
