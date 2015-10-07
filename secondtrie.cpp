#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "trie.h"
#include "variants.h"
#include "initialize.h"
#include <ctime>
using namespace std;

int BARCODE_LENGTH=4;
#define logfilename "mds.log"
/*
void readFileIntoTrie(Trie* trie, int ** ppHashMatrixPointer){
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
}*/
int main()
{ 
    clock_t begin = clock();
    cout<<"start"<<endl;
   // int ** ppHashMatrixPointer= initializeHashMtx();
    
    Trie* t = new Trie();
    
    readFileIntoTrie(t);
    cout <<"read file"<<endl;  
   
    t->populateVariants();
    t->printVariants();
    int max=0;
    cout<<t->returnMaxCount(max)<<endl; 
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "I'm done "<< endl;
    cout << elapsed_secs <<endl;
//    ppHashMatrixPointer=NULL;
}

