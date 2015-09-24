#ifndef TRIE_H
#define TRIE_H

#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Trie::addBarcode(string barcode, string sequence, string target, int ** hash_matrix_pointer){
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
            if (hash_matrix_pointer != NULL){
            check_substitutions(sequence, target, current, hash_matrix_pointer);
        }
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

void Trie::print_trie(Node* current, string barcode, int index){
    if (current == NULL){
        current = root();
    }
    barcode[index] = current->content();
    vector <Node*> children = current->children();
    if (!children.empty()){
        for (int i=0; i<children.size(); i++){
            current = children[i];
            index++;
            print_trie(current, barcode, index);
        }
    }
    else if(current->count()!=0){
        cout<<barcode<<" "<<current->count()<<" "<<unhash_variants((current->variants()).at(0)).first<<" "<< unhash_variants((current->variants()).at(0)).second<<endl;
        return;
    }
}

void Trie::print_variants(){
    Trie* variants_trie = new Trie;
    create_variants_trie(variants_trie);
    variants_trie->print_trie();
}

void Trie::create_variants_trie( Trie* variants_trie, Node* current, string barcode, int index){
    if (current == NULL){
        current = root();
    }
    barcode[index] = current->content();
    vector <Node*> children = current->children();
    if (!children.empty()){
        for (int i=0; i<children.size(); i++){
            current = children[i];
            index++;
            create_variants_trie(variants_trie, current, barcode, index);
        }
    }
    else if(current->count()!=0){
        variants_trie->addBarcode(barcode);
        return;
    }
}


#endif

