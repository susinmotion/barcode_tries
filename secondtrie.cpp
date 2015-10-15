#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "trie.h"
#include "variants.h"
#include "initialize.h"
#include <typeinfo>
#include <ctime>
#include <map>
//#include "constants.h"

using namespace std;

#define logfilename "mds.log"
//map <string, int> userDefinedVariables;

int main()
{   cout<<"HI!"<<endl;

    //int BARCODE_LENGTH=4;
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

