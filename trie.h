#include "node.h"
#include <string>
using namespace std;

class Trie {
public:
    void addBarcode(string s);
    int outputBarcodeCount(string s);
    //Node* root;
private:
    Node* root;
};
