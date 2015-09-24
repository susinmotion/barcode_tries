#include "node.h"
#include <string>
using namespace std;

class Trie {
public:
   Trie(){ mRoot = new Node;}
    void addBarcode(string barcode, string sequence="", string target="", int ** hash_matrix_pointer=NULL);
    int outputBarcodeCount(string barcode);
    Node* root();
    void print_trie(Node* current = NULL, string barcode= string(18,'\0'), int index=0);
    void print_variants();
    void create_variants_trie(Trie* variants_trie, Node* current=NULL, string barcode=string(18,'\0'), int index=0);
private:
    Node* mRoot;
};
