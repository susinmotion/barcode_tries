#include "trie.h"
#include "node.h"

int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    trie->outputBarcodeCount("Hell");    

    trie->outputBarcodeCount("Hello");
    cout << "I'm done "<< endl;
    delete trie;
}