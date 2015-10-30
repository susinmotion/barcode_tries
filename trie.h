#ifndef TRIE_H
#define TRIE_H
#include <map>
#include "node.h"
#include <string>
#include <stack>
#include <vector>
using namespace std;

class Trie {
public:
    Trie(){ mRootPointer = new Node; }
    Node* pRootPointer();
    void addBarcode(int ROINumber, int phase, string barcode, string sequence="", string target="");
    void setThresholdROIPhase(int threshold, int numberOfROIs, int numberOfPhases);
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
    int mNumberOfROIs;
    int mNumberOfPhases;
    stack <Node*> mImportantNodes;
    vector <vector <map<pair<int, int>, int> > >mIndels;
    vector< vector <int> > mVariantsCount;
    vector< vector< vector <int> > >mSubstitutions;

};

#endif
