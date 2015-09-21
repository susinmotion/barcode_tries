#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "trie.h"
using namespace std;

void read_file_into_trie(Trie* trie){
	string filename = "shorter.fastq";
    int count=0;    
	ifstream readfile (filename.c_str());

    string barcode;
	int throwout;
	string throwoutstring;

//  string hname = "hist.txt";
//  string gene = "rpob";
//  string aligncheck = "TTCGGTTCCAGCCAGC";
//  int alignshift = 5;
	
    if (readfile.is_open()){ 
        cout<<"file isopen"<<endl;
        getline(readfile,barcode);
        while (readfile>>throwout){
            count++;
            readfile>>barcode;
            if (barcode.find("N")==-1){
          		trie->addBarcode(barcode);
            }
            readfile>>throwoutstring;
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
        cout<<"Barcode "<<barcode<<" was found "<<current->count()<<" times."<<endl;
        return;
    }
}

int main()
{
    Trie* trie = new Trie();
    
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

    read_file_into_trie(trie2);
    current= trie2->root();
    int max=0;
    max=return_max_count(current, max);
    cout<<max<<" is the max."<<endl;    
    cout << "I'm done "<< endl;
    delete trie;
}

