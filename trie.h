#include "node.h"
#include <string>
using namespace std;

class Trie {
public:
   Trie(){ root = new Node;}
    void addBarcode(string s);
    int outputBarcodeCount(string s);
    //Node* root;
private:
    Node* root;
};
