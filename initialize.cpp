#include "trie.h"
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
using namespace std;

string reverseComplement(string sequence){
    map <char, char> complements;
    complements['A']='T';
    complements ['T']='A';
    complements ['G']='C';
    complements ['C']='G';
    complements ['N']='N';

    string reverseComplement="";
 
    for (int i = sequence.length()-1; i>=0; --i){
        reverseComplement = reverseComplement+complements[sequence[i]];
    }
    return reverseComplement;
}

map <string, vector <string> > readConfig(string filename){ //read config file into map of user defined variables
    map <string, vector<string> > userDefinedVariables;
    userDefinedVariables.clear();
    ifstream infile(filename.c_str());
    if (infile.is_open()){
        string key;
        string allValues;
        string value;
        while (infile >> key >> allValues ){
            vector <string> values;
            cout <<key<<" "<<allValues<<endl;
            stringstream ss(allValues);
            while (getline (ss, value, ';')){
                values.push_back(value);
            }

            pair <string, vector<string> > varPair = make_pair (key, values);
            userDefinedVariables.insert(varPair);
        }
    }
    else {
        cout<<"error opening config file "<<filename<<endl;
    }
    return userDefinedVariables;
}
    
vector<Trie*> readFileIntoTrie(string filename){//set constants based on config file
    map <string, vector <string> > userDefinedVariables=readConfig(filename);
    cout<<" done reading config "<<endl;
    const int BARCODE_LENGTH =atoi(userDefinedVariables["BARCODE_LENGTH"][0].c_str() );
    vector <string> FORWARD_ALIGN_SEQ=userDefinedVariables["FORWARD_ALIGN_SEQ"];
    vector <string> REVERSE_ALIGN_SEQ=userDefinedVariables["REVERSE_ALIGN_SEQ"];
    vector <string> TARGET=userDefinedVariables["TARGET"];
    const vector <string> FILENAMES =userDefinedVariables["FILENAME"];
    
    int numberOfROIs=FORWARD_ALIGN_SEQ.size();

    for (int i=0; i<numberOfROIs; ++i){
        FORWARD_ALIGN_SEQ.push_back(reverseComplement(FORWARD_ALIGN_SEQ[i]));
        REVERSE_ALIGN_SEQ.push_back(reverseComplement(REVERSE_ALIGN_SEQ[i]));
        TARGET.push_back(reverseComplement(TARGET[i]));
    }
        for (int i=0; i<FORWARD_ALIGN_SEQ.size(); ++i){
        cout<<FORWARD_ALIGN_SEQ[i]<<" "<<REVERSE_ALIGN_SEQ[i]<<" "<<TARGET[i]<<endl;

    }
    vector<Trie*> tries;
    for (int i=0; i<numberOfROIs; ++i){
        tries.push_back(new Trie);
        cout <<"made a trie"<<endl;
        tries.at(i)->setThresholdOfImportance( atoi (userDefinedVariables["THRESHOLD_OF_IMPORTANCE"].at(0).c_str()) );
    }
    for (int i=0; i<FILENAMES.size(); ++i){
        ifstream readfile (FILENAMES[i].c_str());

        int count=0;
        string sequence;
        string barcode;
        string throwoutstring;
        int indexForwardAlign;
        int indexReverseAlign;
        if (readfile.is_open()){
            cout<<userDefinedVariables["FILENAME"][i]<<" is open"<<endl;
            while (getline(readfile,throwoutstring)){//read sequence. 4 lines is a read. 2nd line has sequence
                count++;
                readfile>>sequence;
                for (int i=0; i<FORWARD_ALIGN_SEQ.size(); ++i){
                    indexForwardAlign=sequence.find(FORWARD_ALIGN_SEQ[i],BARCODE_LENGTH);//find forward and reverse alignment sequences
                    indexReverseAlign=sequence.find(REVERSE_ALIGN_SEQ[i],BARCODE_LENGTH+FORWARD_ALIGN_SEQ[i].length());
                    if ((indexForwardAlign != -1) && (indexReverseAlign != -1) ){//if align.seq found, add read to trie
                        barcode=sequence.substr(indexForwardAlign-BARCODE_LENGTH, BARCODE_LENGTH);//extract barcode and read from full sequence
                        sequence=sequence.substr(BARCODE_LENGTH+FORWARD_ALIGN_SEQ[i].length(), indexReverseAlign-BARCODE_LENGTH-FORWARD_ALIGN_SEQ[i].length());//maybe rename this variable at some point
                        cout<<barcode<<" "<<sequence<<" "<<TARGET[i]<<endl;
                        tries[i%numberOfROIs]->addBarcode(barcode,sequence, TARGET[i]);

                        break;
                    }
                }
                getline(readfile,throwoutstring);
                getline(readfile,throwoutstring);
                getline(readfile,throwoutstring);                 
            }
        }
        else {
            cout<<"Error opening file "<< userDefinedVariables["FILENAME"][i]<<endl;
        }
    }
    return tries;
}

