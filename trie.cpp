#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <typeinfo>
using namespace std;

int Trie::returnMaxCount(int& max,Node* pCurrentNode ){
    if (pCurrentNode==NULL){
        pCurrentNode=pRootPointer();
    }

    vector <Node*> children = pCurrentNode->children();

    if (!children.empty()){
        for (int i=0; i<children.size(); i++){
            pCurrentNode = children[i];
            returnMaxCount(max, pCurrentNode);
        }
    }
    else if((pCurrentNode->count()!=0) && (pCurrentNode->count()>max) ){
        max=pCurrentNode->count();
        return max;
    }
    return max;
}


void Trie::addBarcode(string barcode, string sequence, string target, int ** ppHashMatrixPointer){
    Node* pCurrentNode = mRootPointer;

    if ( barcode.length() == 0 ){
	pCurrentNode->setCount(); // an empty barcode
	return;
    }
    for ( int i = 0; i < barcode.length(); i++ )//go through barcode base by base. if it's in the trie, continue. if not, add it.
    {  
	Node* pChildNode = pCurrentNode->findChild(barcode[i]);
	if ( pChildNode != NULL ){
	    pCurrentNode = pChildNode;
        }
	else {
	    Node* pTmp = new Node();
	    pTmp->setContent(barcode[i]);
	    pCurrentNode->appendChild(pTmp);
	    pCurrentNode = pTmp;
	}

	if ( i == barcode.length() - 1 ){//if we are at the end of the barcode, check for variants.
	    checkVariants(sequence, target, pCurrentNode, ppHashMatrixPointer);
            pCurrentNode->setCount();
            if (pCurrentNode->count()==mThresholdOfImportance){//if there are enough reads, add pointer to list of important nodes for output later
                addImportantNode(pCurrentNode);
            }
        }
    }
}
stack <Node*> Trie::importantNodes(){
    return mImportantNodes;
}

void Trie::populateVariants(){
   for (int i=0; i<2000;++i){//initialize variant counts hash array to 0
       mVariantCounts[i]=0;
   }
  cout<<mImportantNodes.size()<<"=number of important nodes"<<endl;
    while (!mImportantNodes.empty()){//go through important nodes and increment value in variant counts hash array as varaints are found.
       if (!mImportantNodes.top()->isTrash()){
           vector <int> currentSubstitutions = mImportantNodes.top()->substitutions();
           while (!currentSubstitutions.empty()){
                int currentSubstitution = currentSubstitutions.back();
                currentSubstitutions.pop_back();
                mVariantCounts[currentSubstitution]++;
                mImportantVariantsCount++;
            }
        }
        mImportantNodes.pop();
    }
}

void Trie::addImportantNode(Node* pImportantNode){
    mImportantNodes.push(pImportantNode);
}

int Trie::outputBarcodeCount(string barcode){
    Node* pCurrentNode = mRootPointer;
    int barcodeCount=0;
    for ( int i = 0; i <= barcode.length(); i++ ){
	Node* pNodeAtNextLevel = pCurrentNode->findChild(barcode[i]);
	if (pNodeAtNextLevel == NULL){
	    if ( i == barcode.length() ){        
		barcodeCount = pCurrentNode->count();
	    }
	    cout << barcode << " was found " << barcodeCount << " times." << endl;
	    return barcodeCount;
	}
	pCurrentNode = pNodeAtNextLevel;
    }
    return barcodeCount;
}

Node* Trie::pRootPointer(){
    return mRootPointer;
}

void Trie::printTrie(Node* pCurrentNode, string barcode, int index){
    if (pCurrentNode == NULL){
	pCurrentNode = pRootPointer();
        cout<<"Barcode  Count"<<endl;
    }
    else{
    barcode[index] = pCurrentNode->content();
            index++;
    }
    vector <Node*> children = pCurrentNode->children();
    if (!children.empty()){
	for (int i=0; i<children.size(); i++){
	    pCurrentNode = children[i];
	    printTrie(pCurrentNode, barcode, index);
	}
    }
    else if(pCurrentNode->count()!=0){
       cout<<barcode<<" "<<pCurrentNode->count()<<endl;
       if (!pCurrentNode->substitutions().empty()){
           cout<<" "<<unhashSubstitutions((pCurrentNode->substitutions()).back()).first<<" "<< unhashSubstitutions((pCurrentNode->substitutions()).back()).second<<endl;
       }
       return;
    }
}
void Trie::printVariants(){
    for (int i=0; i<2000;++i){//unhash and output variants found in variant counts hash array. Output count/total count for each variant.
        int count =mVariantCounts[i];
        if (count != 0){
            cout<<unhashSubstitutions(i).first<<" "<<unhashSubstitutions(i).second<<" "<<float(count)/mImportantVariantsCount<<"%"<<endl;
        }
    }
}

void Trie::setThresholdOfImportance(int threshold){
    mThresholdOfImportance=threshold;
}

