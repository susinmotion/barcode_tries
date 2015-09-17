#include "node.h"

    Node::Node() { mContent = ' '; mCount = 0; }
    
Node::~Node() {}

    char Node::content() { return mContent; }

    void Node::setContent(char c) { mContent = c; }

    int Node::count() { return mCount; }

    void Node::setCount() { mCount++; cout << "count=" <<mCount << endl;}

    Node* Node::findChild(char c);

    void Node::appendChild(Node* child) { mChildren.push_back(child); }

    vector<Node*> Node::children() { return mChildren; }
