#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "trie.h"
using namespace std;
#include <ctime>

#define BARCODE_LENGTH 14
#define logfilename "mds.log"

void read_file_into_trie(Trie* trie){
    string filename = "/mnt/storage/data/justin/Archive/miseq/Data/Intensities/BaseCalls/1_S1_L001_R1_001.fastq";
    int count=0;    
    ifstream readfile (filename.c_str());

    string alignSequence="GTTCTTCGG";
    string sequence;
    string barcode;
    string throwoutstring;
    int indexOfAlign;

//  string hname = "hist.txt";
//  string gene = "rpob";
//  string aligncheck = "TTCGGTTCCAGCCAGC";
//  int alignshift = 5;
    
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
            trie->addBarcode(barcode);
            readfile>>throwoutstring;
            getline(readfile, throwoutstring);
            getline(readfile,throwoutstring);
        }
    }
}

int return_max_count(Node* current, int &max ){
    vector <Node*> children = current->children();
    
    if (!children.empty()){
        for (int i=0; i<children.size(); i++){
            current = children[i];
            return_max_count(current, max);
        }
    } 
    else if((current->count()!=0) && (current->count()>max) ){
        max=current->count();
        return max;
    }   
    return max;
}

void print_trie(Node* current, string barcode, int index){
    barcode[index] = current->content();
    vector <Node*> children = current->children();
    if (!children.empty()){
        for (int i=0; i<children.size(); i++){
            current = children[i];
            index++;
            print_trie(current, barcode, index);
        }
    }
    else if(current->count()!=0){
        cout<<barcode<<" "<<current->count()<<endl;
        return;
    }
}

int main()
{
    Trie* trie = new Trie();
  /* 
    trie->addBarcode("Hello");
    trie->addBarcode("TestingMore");
    trie->addBarcode("TestingMore");
    trie->addBarcode("TestingMore");
    trie->addBarcode("SomeMoreString");
    trie->addBarcode("Thisissuperlong");
    trie->outputBarcodeCount("Hell");    
    trie->outputBarcodeCount("Thisissuperlonghowillyouprint,huh?");
    trie->outputBarcodeCount("Hello");
    trie->outputBarcodeCount("Hellow");    

    Node* current = trie->root();
    cout<<endl<<"printing the trie"<<endl;
    print_trie(current, string(1000,'\0'), 0);

    Trie* trie2 = new Trie();
    trie2->outputBarcodeCount("testing");
    //output barcode count and print trie don't work until something has been put in the trie.
*/  clock_t begin = clock();
    read_file_into_trie(trie);
    Node* current= trie->root();
    int max=0;
    ofstream writefile;
    print_trie(current, string(1000,'\0'), 0);
    max=return_max_count(current, max);
    cout<<max<<" is the max."<<endl;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "I'm done "<< endl;
    cout << elapesd_secs <<endl;
    delete trie;
}

