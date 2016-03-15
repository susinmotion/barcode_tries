#include <iostream>
#include "initialize.h"
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include "trie.h"

using namespace std;

int main(){  //file config.cfg contains a list of config files
    clock_t begin = clock();
    cout<<"start"<<endl;
    

    Trie* trie = readFileIntoTrie("config.cfg");

    cout <<"read file"<<endl;  
    

    //trie->printTrieImportantOnly();
    trie->populateAndPrintVariants();
    trie->printCounts();       
   // trie->printTrie();

    //int max=0; //is there a better way to do this max situation?
    //cout<<t->returnMaxCount(max)<<" is the max count"<<endl; 
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "I'm done "<< endl;
    cout << elapsed_secs <<endl;
    
}

