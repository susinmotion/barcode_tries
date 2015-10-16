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
void Node::replaceSubstitutions(vector<int>currentSubstitutions){//check substitutions found in this read against those from other reads of this barcode. Non-matches are listed as unconfirmed
    cout<<mSubstitutions.size()<<" this is the number of substitutuiosn listed"<<endl;
    if (mCount>0){
        vector <int> confirmedSubstitutions;
        for (int i=0; i<mSubstitutions.size(); ++i){//go through existing substitutions. if an item is there but isn't in the new list, mark it as uncertain
            int substitutionHash;
            vector<int>::iterator pos = find(currentSubstitutions.begin(), currentSubstitutions.end(), mSubstitutions[i]);
            if (pos == currentSubstitutions.end() ){
                substitutionHash = (mSubstitutions[i]/5)*5+4;
                cout<<substitutionHash<< "is being added to confirmedSubstitutions just got edited"<<endl;
            }
            else {
                substitutionHash = mSubstitutions[i];
                cout<<substitutionHash<< "is being added to confirmedSubstitutions about to be edited"<<endl;
                currentSubstitutions.erase(pos);
            }
            confirmedSubstitutions.push_back(substitutionHash);
        }
        for (int i=0; i<currentSubstitutions.size(); ++i){//hashes remaining in currentSubstitutions are unconfirmed
            confirmedSubstitutions.push_back( (currentSubstitutions[i]/5)*5+4 );
            cout<<((currentSubstitutions[i]/5 )* 5+4)<< " is being added to confirmedSubstitutions as an edited hash"<<endl;        
        }
        mSubstitutions = confirmedSubstitutions;//replace existing substitutions with confirmed substitutions
    }
    else {//if this is the first read, no check is necessary
        cout<<currentSubstitutions.front()<<" gets an automatic pass since it's the first read"<<endl;
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

