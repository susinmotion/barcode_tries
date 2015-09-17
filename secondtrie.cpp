#include <iostream>
#include <vector>
using namespace std;
#include "node.h"
#include "trie.h"
/*
class Node {
public:
    Node() { mContent = ' '; mCount = 0; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    int count() { return mCount; }
    void setCount() { mCount++; cout << "count=" <<mCount << endl;}
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    int mCount;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addBarcode(string s);
    int outputBarcodeCount(string s);
    void deletBarcode(string s);
private:
    Node* root;
};
*/
Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}
/*
Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}
*/
void Trie::addBarcode(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setCount(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setCount();
    }
}


int Trie::outputBarcodeCount(string s)
{
    Node* current = root;
    int barcodeCount=0;
    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL ){
                barcodeCount= current->count();
		cout << s << " was found " << barcodeCount << " times." << endl;
		return barcodeCount;
		}
            current = tmp;
        }
}
    return barcodeCount;
}


// Test program
int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    trie->outputBarcodeCount("Hell");    

    trie->outputBarcodeCount("Hello");
    cout << "I'm done "<< endl;
    delete trie;
}

