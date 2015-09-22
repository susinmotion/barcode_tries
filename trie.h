#include "node.h"
#include <string>
using namespace std;

class Trie {
public:
   Trie(){ mRoot = new Node;}
    void addBarcode(string barcode, string sequence, string target);
    int outputBarcodeCount(string barcode);
    Node* root();
private:
    Node* mRoot;
};
