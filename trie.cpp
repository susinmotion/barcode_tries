#ifndef TRIE_H
#define TRIE_H

#include "trie.h"
#include "node.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Trie::addBarcode(string barcode, string sequence, string target){
    Node* current = mRoot;
    if ( barcode.length() == 0 ){
        current->setCount(); // an empty word
        return;
    }
    for ( int i = 0; i < barcode.length(); i++ )
    {   
        Node* child = current->findChild(barcode[i]);
        if ( child != NULL )
            current = child;
        else{
            Node* tmp = new Node();
            tmp->setContent(barcode[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == barcode.length() - 1 )
            current->setCount();
            vector<int> variants =  check_substitutions(sequence, target);
    }
}

int Trie::outputBarcodeCount(string barcode){
    Node* current = mRoot;
    int barcodeCount=0;
    for ( int i = 0; i <= barcode.length(); i++ ){
        Node* nodeAtNextLevel = current->findChild(barcode[i]);
        if (nodeAtNextLevel == NULL){
            if ( i == barcode.length() ){        
                barcodeCount = current->count();
            }
            cout << barcode << " was found " << barcodeCount << " times." << endl;
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

