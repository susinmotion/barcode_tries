#include <vector>
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

vector<int> Node::variants(){
    return mVariants;
}

void Node::appendVariant(int variant) {
   mVariants.push_back(variant);
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

