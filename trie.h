#include <string>
class Trie {
public:
    void addBarcode(string s);
    int outputBarcodeCount(string s);
private:
    Node* root;
};
