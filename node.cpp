#include <vector>
#include <stack>
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
bool Node::hasIndel(){
   return mHasIndel;
}
void Node::setIndel(pair<int,int> posLength){
    mHasIndel=true;
    mIndel=posLength;
}
pair <int, int> Node::indel(){
    return mIndel;
}
 
bool Node::hasVariant(){
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

