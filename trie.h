#ifndef TRIE_H
#define TRIE_H
#include <map>
#include "node.h"
#include <string>
#include <set>
#include <vector>
using namespace std;

class Trie {
public:
    Trie(){ mRootPointer = new Node; }
    Node* pRootPointer();
    void addBarcode(int ROINumber, int phase, string barcode, string sequence="", string target="");
    void setThresholdROIPhaseGenesBarcodelenTargetlen(vector <int> threshold, int numberOfROIs, int numberOfPhases, vector <string> genes, int barcodeLength, vector <int> targetLength);
    vector< vector<set <Node*> > >importantNodes();
    void addImportantNode( Node* importantNodePointer, int ROINumber, int phase );
    void populateVariants(int threshold);
    void printVariants(int threshold);
    void printTrieImportantOnly( Node* pCurrentNode=NULL, string barcode=string(18, '\0'), int index=0 );
    void printTrie( Node* pCurrentNodePointer = NULL, string barcode= string(18,'\0'), int index=0 );
    int returnBarcodeCount(string barcode);
    int returnMaxCount( int& max, Node* pCurrentNode=NULL );
    void printCounts();
    void populateAndPrintVariants();

private:
    Node* mRootPointer;
    vector <int> mThresholdsOfImportance;
    int mNumberOfROIs;
    int mNumberOfPhases;
    int mBarcodeLength;
    vector< int > mTargetLength;
    vector< vector <vector< int > > >mCounts;
    vector< vector <set <Node*> > >mImportantNodes;
    vector< vector <map<pair<int, int>, int> > >mIndels;
    vector< vector <int> > mVariantsCount;
    vector< vector <int> > mSubstitutionsCount;
    vector< vector <int> > mNodesChecked;
    vector< vector< map <int,int> > >mSubstitutions;
    vector< string> mGenes;

};

#endif
