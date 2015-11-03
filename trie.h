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
    void setThresholdROIPhaseGenes(int threshold, int numberOfROIs, int numberOfPhases, vector <string> genes);
    vector< vector<stack <Node*> > >importantNodes();
    void addImportantNode(Node* importantNodePointer, int ROINumber, int phase);
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
    vector< vector <stack <Node*> > >mImportantNodes;
    vector< vector <map<pair<int, int>, int> > >mIndels;
    vector< vector <int> > mVariantsCount;
    vector< vector <int> > mNodesChecked;
    vector< vector< map <int,int> > >mSubstitutions;
    vector< string> mGenes;

};

#endif
