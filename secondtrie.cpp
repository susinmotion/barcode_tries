#include <iostream>
#include "initialize.h"
#include <ctime>

using namespace std;

int main(){  
    clock_t begin = clock();
    cout<<"start"<<endl;
    
    Trie* t = new Trie();
    
    readFileIntoTrie(t);
    cout <<"read file"<<endl;  
   
    t->populateVariants();
    t->printVariants();
    //int max=0; //is there a better way to do this max situation?
    //cout<<t->returnMaxCount(max)<<" is the max count"<<endl; 
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "I'm done "<< endl;
    cout << elapsed_secs <<endl;
}

