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
void Node::replaceSubstitutions(vector<int>substitutions){//** I know why the hash shifting happens in 2 parts, but it's kind of icky...
    for (int i=0; i<mSubstitutions.size(); ++i){//go through existing substitutions. if an item is there but isn't in the new list, mark it as uncertain
        if (find(substitutions.begin(), substitutions.end(), mSubstitutions[i])==substitutions.end()){
            substitutions.push_back((mSubstitutions[i]/5)*5+4);
            cout<<mSubstitutions[i]<<" substitution was found earlier but not present in this round---S, W or S, different S"<<endl;
        }
    }
    mSubstitutions = substitutions;
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

