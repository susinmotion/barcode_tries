#include <iostream>
#include <vector>
#include <string>
#include "node.h"
#include "trie.h"

#define ALPHABET_SIZE 4;
using namespace std;

//I want to start at the root of the tree, if it has a value, print it.
//if it doesn't, iterate through the children and call the function recursively

/*void print_trie(Node* current, string outputString=string(14,'\0'), int index = 0)
{
	outputString[index] = current->content();
	vector <Node*> children = current->children();
	if (!children.empty()){

		for (int i=0; i<children.size(); i++){

			current = children[i];

			print_trie(current);
		}
	}
}*/

int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

  //  trie->outputBarcodeCount("Hell");    

    //trie->outputBarcodeCount("Hello");

   // Node* current = trie->root();
   // print_trie(current);

    cout << "I'm done "<< endl;
    delete trie;
}

