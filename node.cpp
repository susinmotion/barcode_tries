#include <vector>
#include <algorithm>
#include "node.h"
#include "leafdata.h"
#include <iostream>
using namespace std;

char Node::content() {
    return mContent;
}

void Node::setContent(char c) {
    mContent = c;
}

vector<Node*> Node::children() {
    return mChildren; 
}

void Node::appendChild(Node* pChild) {
    mChildren.push_back(pChild); 
}

Node* Node::findChild(char c){
    for ( int i = 0; i < mChildren.size(); i++ ) {
        Node* pTmp = mChildren.at(i);
        if ( pTmp->content() == c ){
            return pTmp;
        }
    }
    return NULL;
}

void Node::initializeLeafData(int numberOfROIs, int numberOfPhases){
    mLeafData= vector<vector <LeafData*> >(numberOfROIs, vector<LeafData*> (numberOfPhases, NULL));
}

vector <vector<LeafData*> > Node::leafData(){
    return mLeafData;
}

void Node::setLeafData(int ROINumber, int phase, LeafData* data){
    mLeafData[ROINumber][phase]=data;
}
