#ifndef TRIE_H
#define TRIE_H

#include "node.h"
#include <string>
#include<stack>
using namespace std;

class Trie {
public:
    Trie(){ mRootPointer = new Node; }
    void addBarcode(string barcode, string sequence="", string target="", int ** ppHashMatrixPointer=NULL);
    stack <Node*> importantNodes();
    void addImportantNode(Node* importantNodePointer);
    int outputBarcodeCount(string barcode);
    Node* pRootPointer();
    void printTrie(Node* pCurrentNodePointer = NULL, string barcode= string(18,'\0'), int index=0);
    void printVariants();
    void populateVariants();
    int returnMaxCount(int& max, Node* pCurrentNode=NULL );
    void setThresholdOfImportance(int threshold);
private:
    Node* mRootPointer;
    stack <Node*> mImportantNodes;
    int  mVariantCounts [2000];
    int mImportantVariantsCount;
    int mThresholdOfImportance;
};

#endif
