#include <vector>
#include "node.h"
#include <iostream>
using namespace std;

//Node::Node() { mContent = ' '; mCount = 0; }
    
//Node::~Node() {}

    char Node::content() { return mContent; }

    void Node::setContent(char c) { mContent = c; }

    int Node::count() { return mCount; }

    void Node::setCount() { mCount++; cout << "count=" <<mCount << endl;}
    
void Node::appendChild(Node* child) { mChildren.push_back(child); }

    vector<Node*> Node::children() { return mChildren; }

