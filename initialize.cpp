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
//    string filename = "/mnt/storage/data/justin/Archive/miseq/Data/Intensities/BaseCalls/1_S1_L001_R1_001.fastq";
    string filename = userDefinedVariables["filename"];
    string alignSequenceStart=userDefinedVariables["alignSequenceStart"];
    string alignSequenceFinish=userDefinedVariables["alignSequenceFinish"];
    string target=userDefinedVariables["target"];


    int count=0;
    ifstream readfile (filename.c_str());
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
            cout<<sequence<<" "<<barcode<<endl;
            trie->addBarcode(barcode,sequence, target, ppHashMatrixPointer);
            readfile>>throwoutstring;
            getline(readfile, throwoutstring);
            getline(readfile,throwoutstring);
        }
    }
}
