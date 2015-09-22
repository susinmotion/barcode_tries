#include "node.h"
#include <string>
using namespace std;

class Trie {
public:
   Trie(){ mRoot = new Node;}
    void addBarcode(string s);
    int outputBarcodeCount(string s);
    Node* root();
private:
    Node* mRoot;
};
