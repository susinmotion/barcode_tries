#ifndef TRIE_H
#define TRIE_H

#include "node.h"
#include <string>
#include <stack>
using namespace std;

class Trie {
public:
    Trie(){ mRootPointer = new Node; }
    Node* pRootPointer();
    void addBarcode(string barcode, string sequence="", string target="");
    void setThresholdOfImportance(int threshold);
    stack <Node*> importantNodes();
    void addImportantNode(Node* importantNodePointer);
    void populateVariants();
    void printVariants();
    void printTrie(Node* pCurrentNodePointer = NULL, string barcode= string(18,'\0'), int index=0);
    int returnBarcodeCount(string barcode);
    int returnMaxCount(int& max, Node* pCurrentNode=NULL );
private:
    Node* mRootPointer;
    int mThresholdOfImportance;
    stack <Node*> mImportantNodes;
    int mVariantCounts [2000];
    int mImportantVariantsCount;
};

#endif
