#ifndef TRIE_H
#define TRIE_H

#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
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
	if ( i == barcode.length() - 1 ){
	    if (hash_matrix_pointer != NULL){
	    check_substitutions(sequence, target, current, hash_matrix_pointer);
	    }
            current->setCount();
            if (current->count()==3){
                Node* important_node = current;
                add_important_node(important_node);
            }
        }
    }
}
stack <Node*> Trie::importantNodes(){
    return mImportantNodes;
}

//int[] Trie::variant_counts(){
  //  return mVariant_counts;
//}
/*
void Trie::populate_variants(){
   1;// while (!mImportantNodes.empty()){
        Node* current = mImportantNodes.top();
        mImportantNodes.pop();
        int current_variant = current->variants().at(0);
        variant_counts_ptr()[current_variant]++;
    }
}
*/

void Trie::populate_variants(){
   for (int i=0; i<2000;++i){
       mVariant_counts[i]=0;
   }
   cout<<mImportantNodes.size()<<endl;
   Node* current;
    while (!mImportantNodes.empty()){
        current = mImportantNodes.top();
        int current_count = current->count();
        cout<<current_count<<endl;
        current = NULL;
        mImportantNodes.pop();
        mVariant_counts[current_count]++;
        cout<<mVariant_counts[current_count]<<endl;
    }
}

void Trie::add_important_node(Node* important_node){
    mImportantNodes.push(important_node);
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
       cout<<barcode<<" "<<current->count()<<endl;
       cout<<" "<<unhash_variants((current->variants()).at(0)).first<<" "<< unhash_variants((current->variants()).at(0)).second<<endl;
       return;
    }
}
void Trie::print_variants(){
    for (int i=0; i<2000;++i){
        int count =mVariant_counts[i];
        if (count != 0){
            //cout<<count<<" "<<unhash_variants(i).first<<" "<<unhash_variants(i).second<<endl;
            cout<<count<<"samples were found "<<i<<"times"<<endl;
        }
    }
}
/*
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
        variants_trie->addBarcode(char((current->variants()).at(0)));
        return;
    }
}
*/

#endif

