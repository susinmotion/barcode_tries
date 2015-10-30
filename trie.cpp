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

void Trie::addBarcode(int ROINumber, int phase, string barcode, string sequence, string target){
    Node* pCurrentNode = mRootPointer;
    if ( barcode.length() == 0 ){
        pCurrentNode->initializeLeafData(mNumberOfROIs, mNumberOfPhases); // an empty barcode
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
            if (pCurrentNode->leafData().empty()){
                pCurrentNode->initializeLeafData(mNumberOfROIs, mNumberOfPhases);
            }
            LeafData* pCurrentData= pCurrentNode->leafData()[ROINumber][phase];
            if (pCurrentData==NULL){
                pCurrentData=new LeafData;
            }
            checkVariants(sequence, target, pCurrentData);
            pCurrentData->setCount();
            pCurrentNode->setLeafData(ROINumber, phase, pCurrentData);
            if (pCurrentNode->leafData()[ROINumber][phase]->count()==mThresholdOfImportance){//if there are enough reads, add pointer to list of important nodes for output later
                addImportantNode(pCurrentNode);
            }
        }
    }
}

void Trie::setThresholdROIPhase(int threshold, int numberOfROIs, int numberOfPhases){
    mThresholdOfImportance=threshold;
    mNumberOfROIs= numberOfROIs;
    mNumberOfPhases = numberOfPhases;
}

stack <Node*> Trie::importantNodes(){
    return mImportantNodes;
}

void Trie::addImportantNode(Node* pImportantNode){
    mImportantNodes.push(pImportantNode);
}

void Trie::populateVariants(){
    mVariantsCount= vector <vector<int> >(mNumberOfROIs, vector<int>(mNumberOfPhases,  0));
    mSubstitutions= vector<vector <vector<int> > >(mNumberOfROIs, vector<vector<int> >(mNumberOfPhases, vector<int> (2000, 0)));
    map<pair<int,int>, int> empty_map;
    mIndels = vector<vector <map <pair<int,int>, int> > >( mNumberOfROIs, vector< map<pair<int,int>, int> >(mNumberOfPhases, (empty_map)));
              

    cout<<mImportantNodes.size()<<"=number of important nodes"<<endl;
    cout<<mNumberOfROIs<< " rois"<<endl;
    cout<<mNumberOfPhases<<" phases"<<endl;
    while (!mImportantNodes.empty()){//go through important nodes and increment value in variant counts hash array as varaints are found.
        for (int i=0; i<mNumberOfROIs; ++i){
            for (int j=0; j<mNumberOfPhases; ++j){
                LeafData* currentData=mImportantNodes.top()->leafData()[i][j];
                if (currentData!=NULL){
                   if (!currentData->isTrash()){
                        if (currentData->hasIndel()==true){
                            mVariantsCount[i][j]++;
                            if (mIndels[i][j][currentData->indel()]){
                                mIndels[i][j][currentData->indel()]++;
                            }
                            else{
                                mIndels[i][j][currentData->indel()]=1;
                            }
                        }
                        else{
                            vector <int> currentSubstitutions = currentData->substitutions();
                            while (!currentSubstitutions.empty()){
                                int currentSubstitution = currentSubstitutions.back();
                                currentSubstitutions.pop_back();
                                mSubstitutions[i][j][currentSubstitution]++;
                                mVariantsCount[i][j]++;
                            }
                        }
                    }

                }
            }
        }
        mImportantNodes.pop();       
    }
}

void Trie::printVariants(){
    cout<<"printing trie "<<endl;

    for (int i=0; i<mNumberOfROIs; ++i){
        for (int j=0; j<mNumberOfPhases; ++j){
            if (mVariantsCount[i][j]!=0){
                cout<<"ROI "<<i<<" Phase "<<j<<" Total variants found "<<mVariantsCount[i][j]<<endl;
                for (int k=0; k<2000;++k){//unhash and output variants found in variant counts hash array. Output count/total count for each variant.
                    int count= mSubstitutions[i][j][k];
                    if (count != 0){
                        cout<<unhashSubstitutions(i).first<<" "<<unhashSubstitutions(i).second<<" "<<count<<endl;
                    } 
                
                }
                for(map< pair<int, int>, int>::const_iterator it = mIndels[i][j].begin(); it != mIndels[i][j].end(); ++it){
                    cout << it->first.first << " " << it->first.second << " " << it->second << endl;
                }
            }
        }
    }  
}
/* WHAT do we actually want for this? For a given ROI and a given PHase, the barcode count? OR the total count regardless?
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
*/

/*same here
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
*/
/*and here. Maybe a barcode needs to have a total count at the node level
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

*/
