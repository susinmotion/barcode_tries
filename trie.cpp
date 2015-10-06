#ifndef TRIE_H
#define TRIE_H

#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <typeinfo>
using namespace std;


void Trie::addBarcode(string barcode, string sequence, string target, int ** hash_matrix_pointer){
    Node* current = mRoot;
    int rThresh = 3;
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
            if (current->count()==rThresh){
                add_important_node(current);
               // Node* temp=new Node(current);
               // cout<<typeid(temp).name()<<endl;
               // cout<<temp<<"address of temp"<<endl;
                //set_most_recent_3(current);
               
               // temp=NULL;
  //              cout<<current<<" address of current"<<endl;
    //            cout <<most_recent_3_node->count()<<"Most recent 3 count"<<endl;
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
  cout<<mImportantNodes.size()<<"=number of important nodes"<<endl;
   Node* current;
    while (!mImportantNodes.empty()){
        current = mImportantNodes.top();
      //  int current_count = mImportantNodes.top()->count();
        if (!current->variants().empty()){
            //cout<<"there's a variant "<<current->variants().at(0)<<endl;
            int current_variant = current->variants().at(0);
            mVariant_counts[current_variant]++;
            mImportantVariantsCount++;
        }
            mImportantNodes.pop();
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
    else{
    barcode[index] = current->content();
            index++;
    }
    vector <Node*> children = current->children();
    if (!children.empty()){
	for (int i=0; i<children.size(); i++){
	    current = children[i];
	    print_trie(current, barcode, index);
	}
    }
    else if(current->count()!=0){
       cout<<barcode<<"  barcode  -> count :"<<current->count()<<endl;
       if (!current->variants().empty()){
           cout<<" "<<unhash_variants((current->variants()).at(0)).first<<" "<< unhash_variants((current->variants()).at(0)).second<<endl;
       }
       return;
    }
}
void Trie::print_variants(){
    for (int i=0; i<2000;++i){
        int count =mVariant_counts[i];
        if (count != 0){
            cout<<unhash_variants(i).first<<" "<<unhash_variants(i).second<<" "<<float(count)/mImportantVariantsCount<<"%"<<endl;
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

