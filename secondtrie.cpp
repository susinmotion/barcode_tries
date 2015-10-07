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

int main()
{ 
    clock_t begin = clock();
    cout<<"start"<<endl;
    
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
}

