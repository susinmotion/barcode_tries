#include "trie.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*
Trie::Trie()
{
    mRoot = new Node();
}

Trie::~Trie()
{
    // Free memory
}

Node* Trie::root(){
    return root;
}
*/
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
	     cout<<child->content()<<endl;
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
