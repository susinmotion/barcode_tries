#include "trie.h"

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
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
