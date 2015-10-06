#include "node.h"
#include <string>
#include<stack>
using namespace std;

class Trie {
public:
    Trie(){ mRoot = new Node; }//mVariant_counts={};}
     void addBarcode(string barcode, string sequence="", string target="", int ** hash_matrix_pointer=NULL);
    stack <Node*> importantNodes();
    void add_important_node(Node* important_node);
    int outputBarcodeCount(string barcode);
    Node* root();
    void print_trie(Node* current = NULL, string barcode= string(18,'\0'), int index=0);
    void print_variants();
   // void create_variants_trie(Trie* variants_trie, Node* current=NULL, string barcode=string(18,'\0'), int index=0);
    void populate_variants();
private:
    Node* mRoot;
    stack <Node*> mImportantNodes;
    int  mVariant_counts [2000];
    int mImportantVariantsCount;
};
