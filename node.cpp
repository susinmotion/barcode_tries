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

 Node* Node::findChild(char c)
{cout<<mChildren.empty()<<endl;
        for ( int i = 0; i < mChildren.size(); i++ )
            {
                cout<<i<<endl;
                Node* tmp = mChildren.at(i);
                if ( tmp->content() == c )
                 {
                return tmp;
                }
             }

         return NULL;
}

