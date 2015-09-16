#include <iostream>
#include <vector>
#include <string>
#include "node.h"
#include "trie.h"

using namespace std;


int main()
{
    Trie* trie=new Trie();
    trie->addBarcode("Hello");

    trie->outputBarcodeCount("Hell");    

    trie->outputBarcodeCount("Hello");
    cout << "I'm done "<< endl;
    delete trie;
}
