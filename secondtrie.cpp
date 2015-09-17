#include <iostream>
#include <vector>
using namespace std;
#include "node.h"
#include "trie.h"

void print_trie(Node* current, string outputString=string(14,'\0'), int index = 0)
{
        outputString[index] = current->content();
        vector <Node*> children = current->children();
        if (!children.empty()){

                for (int i=0; i<children.size(); i++){

                        current = children[i];

                        print_trie(current);
                }
        }
	else if(current->count()!=0){
cout<<"Barcode "<<outputString<<" was found "<<current->count()<<" times."<<endl;
}
}

int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    trie->outputBarcodeCount("Hell");    

    trie->outputBarcodeCount("Hello");
    Node* current = trie->root();
    print_trie(current);


    cout << "I'm done "<< endl;
    delete trie;
}

