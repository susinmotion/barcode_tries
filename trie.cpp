#include "trie.h"
#include "node.h"
#include "variants.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#include <set>
using namespace std;

Node* Trie::pRootPointer(){
    return mRootPointer;
}

void Trie::addBarcode(int ROINumber, int phase, string barcode, string sequence, string target){
    Node* pCurrentNode = mRootPointer;
    if (barcode.find('N') != -1){ return;}
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
                addImportantNode(pCurrentNode, ROINumber, phase);
            }
        }
    }
}

void Trie::setThresholdROIPhaseGenesBarcodelenTargetlen(int threshold, int numberOfROIs, int numberOfPhases, vector<string>genes, int barcodeLength, vector <int> targetLength){
    mThresholdOfImportance=threshold;
    mNumberOfROIs= numberOfROIs;
    mNumberOfPhases = numberOfPhases;
    mGenes = genes;
    mTargetLength= targetLength;
    set <Node*> empty_set;
    mImportantNodes=vector <vector <set <Node*> > >(mNumberOfROIs, vector<set<Node* > >(mNumberOfPhases, empty_set));
    mBarcodeLength=barcodeLength;
}

vector< vector< set <Node*> > >Trie::importantNodes(){
    return mImportantNodes;
}

void Trie::addImportantNode(Node* pImportantNode, int ROINumber, int phase){
    mImportantNodes[ROINumber][phase].insert(pImportantNode);
}

void Trie::populateVariants(){
    mVariantsCount= vector <vector<int> >(mNumberOfROIs, vector<int>(mNumberOfPhases,  0));
    mSubstitutionsCount= vector< vector <int> >(mNumberOfROIs, vector<int>(mNumberOfPhases,0 ));
    mNodesChecked= vector <vector<int> >(mNumberOfROIs, vector<int>(mNumberOfPhases,  0));
    map<int, int> empty_map1;
    mSubstitutions= vector<vector <map <int, int> > >( mNumberOfROIs, vector< map<int, int> >(mNumberOfPhases, empty_map1));
    map<pair<int,int>, int> empty_map;
    mIndels = vector<vector <map <pair<int,int>, int> > >( mNumberOfROIs, vector< map<pair<int,int>, int> >(mNumberOfPhases, empty_map));
              
    cout<<mNumberOfROIs<< " rois"<<endl;
    cout<<mNumberOfPhases<<" phases"<<endl;
    int totalImportantNodes=0;
    for (int i=0; i<mNumberOfROIs; ++i){
        for (int j=0; j<mNumberOfPhases; ++j){
            while (!mImportantNodes[i][j].empty()){//go through important nodes and increment value in variant counts hash array as varaints are found. 
                LeafData* currentData=(*mImportantNodes[i][j].begin())->leafData()[i][j];
                totalImportantNodes++;
                if (currentData!=NULL){
                    mNodesChecked[i][j]++;
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
                                //cout<<i<<" "<<j<<" "<<currentSubstitution<<" "<<mSubstitutions[i][j][currentSubstitution]<<endl;
                                mVariantsCount[i][j]++;
                                mSubstitutionsCount[i][j]++;
                            }
                        }
                    }
                   // else{cout<<"Trash"<<endl;}

                }
                mImportantNodes[i][j].erase(mImportantNodes[i][j].begin()); 
            }      
        }
    }
    cout<<totalImportantNodes<<"=number of important nodes"<<endl;
}

void Trie::printTrieImportantOnly(Node* pCurrentNode, string barcode, int index){
//this function needs to be called before populate variants
    if ( pCurrentNode == NULL ){//if this is the first iteration, set current at root of trie
        pCurrentNode = mRootPointer;
        cout<<"Barcode Count"<<endl;
        barcode=string(mBarcodeLength, '\0');
    }
    else{//add the content of this node to the barcode
        barcode[index] = pCurrentNode->content();
        index++;
    }
    vector <Node*> children = pCurrentNode->children();
    if ( !children.empty() ){//go to next level of trie
        for (int i=0; i<children.size(); i++){
            pCurrentNode = children[i];
            printTrieImportantOnly(pCurrentNode, barcode, index);
        }
    }
    else if( !pCurrentNode->leafData().empty() ){//if we reach a leaf, print the count and variants
        ofstream summaryFile;
        summaryFile.open("summaryIMPORTANT.txt", ios::app);
        for (int i=0; i<mNumberOfROIs; ++i){
            for (int j=0; j<mNumberOfPhases; ++j){
                LeafData* currentData= pCurrentNode->leafData()[i][j];
if (currentData!=NULL && !currentData->isTrash() && mImportantNodes[i][j].find(pCurrentNode)!=mImportantNodes[i][j].end() ){
                    summaryFile<<barcode<<" "<<mGenes[i]<<" phase "<<j<<endl;
                    summaryFile<<currentData->count()<<" reads"<<endl;
                    if (!currentData->substitutions().empty()){
                        for (int q=0; q<currentData->substitutions().size(); ++q){
                            summaryFile<<" "<<unhashSubstitutions(currentData->substitutions()[q]).first<<" "<< unhashSubstitutions(currentData->substitutions()[q]).second<<endl;
                        }
                    }
                
                    if (currentData->hasIndel()){                   
                        summaryFile<<currentData->indel().first<<" "<<currentData->indel().second<<endl;
}
                }
            }
        summaryFile.close();
       }

       return;
    }
}


void Trie::printVariants(){
    cout<<"printing trie "<<endl;
    for (int i=0; i<mNumberOfROIs; ++i){
        for (int j=0; j<mNumberOfPhases; ++j){
            if (mVariantsCount[i][j]!=0){
                ostringstream os;
                os<<j;
                string filename= mGenes[i]+"_"+os.str()+".txt";
                string matrixFilename = mGenes[i]+"_"+os.str()+"matrix.txt";
                ofstream outfile;
                ofstream matrixOutfile;
                outfile.open (filename.c_str());
                matrixOutfile.open (matrixFilename.c_str());

                outfile<<"ROI: "<<mGenes[i]<<endl<<"Phase: "<<j<<endl<<"Total nodes checked: "<< mNodesChecked[i][j]<<endl<<"Total variants found: "<<mVariantsCount[i][j]<<endl;
                map<int,int>::iterator it1;
                for (int l=0; l<5; ++l){//go through each base
                    for (int k = 0; k<mTargetLength[i]; ++k){
                        it1=mSubstitutions[i][j].find(k*5+l);
                        if (it1 == mSubstitutions[i][j].end()){
                            matrixOutfile<<left<<setw(15)<<setfill(' ')<<"0";   
                        }
                        else {
                            matrixOutfile<<left<<setw(15)<<setfill(' ')<<it1->second/(float)mSubstitutionsCount[i][j];
                        }
                    }
                    matrixOutfile<<endl;
                }
                for (map <int, int>::const_iterator it=mSubstitutions[i][j].begin(); it != mSubstitutions[i][j].end(); ++it){
                    outfile<<unhashSubstitutions(it->first).first<<" "<<unhashSubstitutions(it->first).second<<" "<< it->second << endl;
                }
                for(map< pair<int, int>, int>::const_iterator it = mIndels[i][j].begin(); it != mIndels[i][j].end(); ++it){
                    outfile << it->first.first << " " << it->first.second << " " << it->second << endl;
                }
                outfile.close();
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


void Trie::printTrie(Node* pCurrentNode, string barcode, int index){


    if ( pCurrentNode == NULL ){//if this is the first iteration, set current at root of trie
        pCurrentNode = mRootPointer;
        cout<<"Barcode Count"<<endl;
        barcode=string(mBarcodeLength, '\0');
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
    else if( !pCurrentNode->leafData().empty()){//if we reach a leaf, print the count and variants
        ofstream summaryFile;
        summaryFile.open("summary.txt", ios::app);
        summaryFile<<"barcode: "<<barcode<<endl;
        for (int i=0; i<mNumberOfROIs; ++i){
            summaryFile<<mGenes[i]<<endl;
            for (int j=0; j<mNumberOfPhases; ++j){
                LeafData* currentData= pCurrentNode->leafData()[i][j];
                if (currentData!=NULL){
                    summaryFile<<"phase "<<j<<endl;

                    if (!currentData->substitutions().empty()){
                        for (int q=0; q<currentData->substitutions().size(); ++q){
                            summaryFile<<" "<<unhashSubstitutions(currentData->substitutions()[q]).first<<" "<< unhashSubstitutions(currentData->substitutions()[q]).second<<endl;
                        }
                    }
                
                    if (currentData->hasIndel()){                   
                        summaryFile<<currentData->indel().first<<" "<<currentData->indel().second<<endl;
}
                }
            }
        summaryFile.close();
       }

       return;
    }
}

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
