#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

Node* Trie::pRootPointer(){
    return mRootPointer;
}

void Trie::addBarcode(string barcode, string sequence, string target){
    Node* pCurrentNode = mRootPointer;

    if ( barcode.length() == 0 ){
        pCurrentNode->setCount(); // an empty barcode
        return;
    }
    for ( int i = 0; i < barcode.length(); i++ ){//go through barcode base by base. if it's in the trie, continue. if not, add it. 
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
            checkVariants(sequence, target, pCurrentNode);
            pCurrentNode->setCount();
            if (pCurrentNode->count()==mThresholdOfImportance){//if there are enough reads, add pointer to list of important nodes for output later
                addImportantNode(pCurrentNode);
            }
        }
    }
}

void Trie::setThresholdOfImportance(int threshold){
    mThresholdOfImportance=threshold;
}

stack <Node*> Trie::importantNodes(){
    return mImportantNodes;
}

void Trie::addImportantNode(Node* pImportantNode){
    mImportantNodes.push(pImportantNode);
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

void Trie::printVariants(){
    for (int i=0; i<2000;++i){//unhash and output variants found in variant counts hash array. Output count/total count for each variant.
        int count =mVariantCounts[i];
        if (count != 0){
            cout<<unhashSubstitutions(i).first<<" "<<unhashSubstitutions(i).second<<" "<<float(count)/mImportantVariantsCount<<endl;
        }
    }
}

int Trie::returnBarcodeCount(string barcode){
    Node* pCurrentNode = mRootPointer;
    int barcodeCount=0;
    for (int i = 0; i <= barcode.length(); i++){//go through the trie until you get to the end of the barcode
        Node* pNodeAtNextLevel = pCurrentNode->findChild(barcode[i]);
        if ( pNodeAtNextLevel == NULL ){
            if ( i == barcode.length() ){        
                barcodeCount = pCurrentNode->count();
            }
            return barcodeCount;
        }
        pCurrentNode = pNodeAtNextLevel;
    }
    return barcodeCount;
}

void Trie::printTrie(Node* pCurrentNode, string barcode, int index){
    if ( pCurrentNode == NULL ){//if this is the first iteration, set current at root of trie
        pCurrentNode = mRootPointer;
        cout<<"Barcode Count"<<endl;
    }
    else{//add the content of this node to the barcode
        barcode[index] = pCurrentNode->content();
        index++;
    }
    vector <Node*> children = pCurrentNode->children();
    if ( !children.empty() ){//go to next level of trie
        for (int i=0; i<children.size(); i++){
            pCurrentNode = children[i];
            printTrie(pCurrentNode, barcode, index);
        }
    }
    else if( pCurrentNode->count()!=0 ){//if we reach a leaf, print the count and variants
       cout<<barcode<<" "<<pCurrentNode->count()<<endl;
       if (!pCurrentNode->substitutions().empty()){
           cout<<" "<<unhashSubstitutions((pCurrentNode->substitutions()).back()).first<<" "<< unhashSubstitutions((pCurrentNode->substitutions()).back()).second<<endl;
       }
       return;
    }
}

int Trie::returnMaxCount(int& max,Node* pCurrentNode ){
    if ( pCurrentNode==NULL ){ //if this is the first time the function is called, set current to root
        pCurrentNode=mRootPointer;
    }

    vector <Node*> children = pCurrentNode->children();

    if ( !children.empty() ){ //if there are still children, go one level down and recurse
        for (int i=0; i<children.size(); i++){
            pCurrentNode = children[i];
            returnMaxCount(max, pCurrentNode);
        }
    }
    else if ( pCurrentNode->count()>max ){//if the current count is greater than the max, reset the max
        max=pCurrentNode->count();
    }
    return max;
}

