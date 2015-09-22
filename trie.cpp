#ifndef TRIE_H
#define TRIE_H

#include "trie.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Trie::addBarcode(string s){
    Node* current = mRoot;
    if ( s.length() == 0 ){
        current->setCount(); // an empty word
        return;
    }
    for ( int i = 0; i < s.length(); i++ )
    {   
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
            current = child;
        else{
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setCount();
    }
}

int Trie::outputBarcodeCount(string s){
    Node* current = mRoot;
    int barcodeCount=0;
    for ( int i = 0; i <= s.length(); i++ ){
        Node* nodeAtNextLevel = current->findChild(s[i]);
        if (nodeAtNextLevel == NULL){
            if ( i == s.length() ){        
                barcodeCount = current->count();
            }
            cout << s << " was found " << barcodeCount << " times." << endl;
            return barcodeCount;
        }
        current = nodeAtNextLevel;
    }
    return barcodeCount;
}

Node* Trie::root(){
    return mRoot;
}

#endif

