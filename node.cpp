#include <vector>
#include <stack>
#include <algorithm>
#include "node.h"
#include <iostream>
using namespace std;

char Node::content() {
    return mContent;
}

void Node::setContent(char c) {
    mContent = c;
}

int Node::count() {
    return mCount;
}

void Node::setCount() {
    mCount++; 
}

vector<int> Node::substitutions(){
    return mSubstitutions;
}

void Node::appendSubstitution(int substitution) {
    mSubstitutions.push_back(substitution);
}
//this is still a little icky...
void Node::replaceSubstitutions(vector<int>currentSubstitutions){//check substitutions found in this read against those from other reads of this barcode. Non-matches are listed as unconfirmed
    if (mCount>0){
        vector <int> confirmedSubstitutions;
        for (int i=0; i<mSubstitutions.size(); ++i){//go through existing substitutions. if an item is there but isn't in the new list, mark it as uncertain
            int substitutionHash;
            vector<int>::iterator pos = find(currentSubstitutions.begin(), currentSubstitutions.end(), mSubstitutions[i]);
            if (pos == currentSubstitutions.end() ){
                substitutionHash = (mSubstitutions[i]/5)*5+4;
            }
            else {
                substitutionHash = mSubstitutions[i];
                currentSubstitutions.erase(pos);
            }
            if ( find(confirmedSubstitutions.begin(), confirmedSubstitutions.end(), substitutionHash)==confirmedSubstitutions.end()){
                confirmedSubstitutions.push_back(substitutionHash);
            }
        }
        for (int i=0; i<currentSubstitutions.size(); ++i){//hashes remaining in currentSubstitutions are marked as uncertain
            int substitutionHash=(currentSubstitutions[i]/5)*5+4;
            if ( find(confirmedSubstitutions.begin(), confirmedSubstitutions.end(), substitutionHash)==confirmedSubstitutions.end()){
                confirmedSubstitutions.push_back(substitutionHash);
            }     
        }
        mSubstitutions = confirmedSubstitutions;//replace existing substitutions with confirmed substitutions
    }
    else {//if this is the first read, no check is necessary
        mSubstitutions = currentSubstitutions;
    }
}

bool Node::hasIndel(){
   return mHasIndel;
}

pair <int, int> Node::indel(){
    return mIndel;
}

void Node::setIndel(pair<int,int> posLength){
    mHasIndel=true;
    mIndel=posLength;
}

bool Node::isTrash(){
    return mIsTrash;
}

void Node::makeTrash(){
    mIsTrash=true;
}

bool Node::hasVariant(){//does this get used?
    return(mHasIndel || !mSubstitutions.empty());
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

