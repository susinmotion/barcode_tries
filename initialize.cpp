#include "trie.h"
#include <string>
#include <map>
#include <fstream>
//#include "constants.h"

using namespace std;

map <string, string> readConfig(){
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
    map <string, string> userDefinedVariables=readConfig();
    int BARCODE_LENGTH=atoi(userDefinedVariables["BARCODE_LENGTH"].c_str() );
//    string FILENAME = "/mnt/storage/data/justin/Archive/miseq/Data/Intensities/BaseCalls/1_S1_L001_R1_001.fastq";
    string ALIGN_SEQUENCE_START=userDefinedVariables["ALIGN_SEQUENCE_START"];
    string ALIGN_SEQUENCE_FINISH=userDefinedVariables["ALIGN_SEQUENCE_FINISH"];
    string TARGET=userDefinedVariables["TARGET"];
    
    trie->setThresholdOfImportance( atoi (userDefinedVariables["THRESHOLD_OF_IMPORTANCE"].c_str()) );
    ifstream readfile (userDefinedVariables["FILENAME"].c_str());

    int count=0;
    string sequence;
    string barcode;
    string throwoutstring;
    int indexOfAlignStart;
    int indexOfAlignFinish;

    int ** ppHashMatrixPointer = initializeHashMtx();

    if (readfile.is_open()){
        cout<<"file isopen"<<endl;
        while (getline(readfile,throwoutstring)){
            count++;
            readfile>>sequence;
            indexOfAlignStart=sequence.find(ALIGN_SEQUENCE_START,BARCODE_LENGTH);
            indexOfAlignFinish=sequence.find(ALIGN_SEQUENCE_FINISH,BARCODE_LENGTH+ALIGN_SEQUENCE_START.length());
            if ((indexOfAlignStart == -1) || (indexOfAlignFinish == -1) ){
                readfile>>throwoutstring;
                getline(readfile,throwoutstring);
                getline(readfile,throwoutstring);
                continue;
            }
            barcode=sequence.substr(indexOfAlignStart-BARCODE_LENGTH, BARCODE_LENGTH);
            sequence=sequence.substr(BARCODE_LENGTH+ALIGN_SEQUENCE_START.length(), indexOfAlignFinish-BARCODE_LENGTH-ALIGN_SEQUENCE_START.length());
            
            cout<<sequence<<" "<<barcode<<endl;
            
            trie->addBarcode(barcode,sequence, TARGET, ppHashMatrixPointer);
            readfile>>throwoutstring;
            getline(readfile, throwoutstring);
            getline(readfile,throwoutstring);
        }
    }
}
