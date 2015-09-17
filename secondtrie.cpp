#include <iostream>
#include <vector>
using namespace std;
#include "node.h"
#include "trie.h"

int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    trie->outputBarcodeCount("Hell");    

    trie->outputBarcodeCount("Hello");
    cout << "I'm done "<< endl;
    delete trie;
}

