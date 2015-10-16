#include "trie.h"
#include <string>
#include <map>
#include <fstream>

using namespace std;

map <string, string> readConfig(){ //read config file into map of user defined variables
    map <string, string> userDefinedVariables;
    userDefinedVariables.clear();
    ifstream infile("example.cfg");
    string key;
    string value;
    while (infile >> key >>value){
        pair <string, string> varPair = make_pair (key, value);
        userDefinedVariables.insert(varPair);
    }
    return userDefinedVariables;
}
    


int ** initializeHashMtx(){//cols 0-4 represent bases ACGTN, in that order. Rows represent position of variant.
    int maxSequenceLength=400;
    int ** ppHashMatrixPointer = new int*[maxSequenceLength];
    short int count;
    for (int row = 0; row < maxSequenceLength; row++){
        ppHashMatrixPointer[row]=new int[5];
        for (int col = 0; col < 5; col++){
            *(* (ppHashMatrixPointer+row)+col) = count;
            count++;
        }
    }
    return ppHashMatrixPointer;
}
void readFileIntoTrie(Trie* trie){//set constants based on config file
    map <string, string> userDefinedVariables=readConfig();
    const int BARCODE_LENGTH=atoi(userDefinedVariables["BARCODE_LENGTH"].c_str() );
//    string FILENAME = "/mnt/storage/data/justin/Archive/miseq/Data/Intensities/BaseCalls/1_S1_L001_R1_001.fastq";
    const string FORWARD_ALIGN_SEQ=userDefinedVariables["FORWARD_ALIGN_SEQ"];
    const string REVERSE_ALIGN_SEQ=userDefinedVariables["REVERSE_ALIGN_SEQ"];
    const string TARGET=userDefinedVariables["TARGET"];
    
    trie->setThresholdOfImportance( atoi (userDefinedVariables["THRESHOLD_OF_IMPORTANCE"].c_str()) );
    ifstream readfile (userDefinedVariables["FILENAME"].c_str());

    int count=0;
    string sequence;
    string barcode;
    string throwoutstring;
    int indexForwardAlign;
    int indexReverseAlign;

    int ** ppHashMatrixPointer = initializeHashMtx();

    if (readfile.is_open()){
        cout<<"file isopen"<<endl;
        while (getline(readfile,throwoutstring)){//read sequence. 4 lines is a read. 2nd line has sequence
            count++;
            readfile>>sequence;
            indexForwardAlign=sequence.find(FORWARD_ALIGN_SEQ,BARCODE_LENGTH);//find forward and reverse alignment sequences
            indexReverseAlign=sequence.find(REVERSE_ALIGN_SEQ,BARCODE_LENGTH+FORWARD_ALIGN_SEQ.length());
            
            getline(readfile,throwoutstring);
            getline(readfile,throwoutstring);
            getline(readfile,throwoutstring);
            
            if ((indexForwardAlign != -1) && (indexReverseAlign != -1) ){//if align.seq found, add read to trie
                barcode=sequence.substr(indexForwardAlign-BARCODE_LENGTH, BARCODE_LENGTH);//extract barcode and read from full sequence
                sequence=sequence.substr(BARCODE_LENGTH+FORWARD_ALIGN_SEQ.length(), indexReverseAlign-BARCODE_LENGTH-FORWARD_ALIGN_SEQ.length());//maybe rename this variable at some point
            
                cout<<sequence<<" "<<barcode<<endl;
            
                trie->addBarcode(barcode,sequence, TARGET, ppHashMatrixPointer);
            }
        }
    }
}
