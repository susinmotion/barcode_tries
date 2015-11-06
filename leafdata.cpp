#include <vector>
#include <stack>
#include <algorithm>
#include "leafdata.h"
#include <iostream>
using namespace std;

int LeafData::count() {
    return mCount;
}

void LeafData::setCount() {
    mCount++; 
}

vector<int> LeafData::substitutions(){
    return mSubstitutions;
}

void LeafData::appendSubstitution(int substitution) {
    mSubstitutions.push_back(substitution);
}
//this is still a little icky...
void LeafData::replaceSubstitutions(vector<int>currentSubstitutions){//check substitutions found in this read against those from other reads of this barcode. Non-matches are listed as unconfirmed
    if (mCount>0){
        vector <int> confirmedSubstitutions;
        for (int i=0; i<mSubstitutions.size(); ++i){//go through existing substitutions. if an item is there but isn't in the new list, mark it as uncertain
            int substitutionHash;
            vector<int>::iterator pos = find(currentSubstitutions.begin(), currentSubstitutions.end(), mSubstitutions[i]);
            if (pos == currentSubstitutions.end() ){
                substitutionHash = (mSubstitutions[i]/5)*5+4;
            }
            else {
                substitutionHash = mSubstitutions[i];
                currentSubstitutions.erase(pos);
            }
            if ( find(confirmedSubstitutions.begin(), confirmedSubstitutions.end(), substitutionHash)==confirmedSubstitutions.end()){
                confirmedSubstitutions.push_back(substitutionHash);
            }
        }
        for (int i=0; i<currentSubstitutions.size(); ++i){//hashes remaining in currentSubstitutions are marked as uncertain
            int substitutionHash=(currentSubstitutions[i]/5)*5+4;
            if ( find(confirmedSubstitutions.begin(), confirmedSubstitutions.end(), substitutionHash)==confirmedSubstitutions.end()){
                confirmedSubstitutions.push_back(substitutionHash);
            }     
        }
        mSubstitutions = confirmedSubstitutions;//replace existing substitutions with confirmed substitutions
    }
    else {//if this is the first read, no check is necessary
        mSubstitutions = currentSubstitutions;
    }
}

bool LeafData::hasIndel(){
   return mHasIndel;
}

pair <int, int> LeafData::indel(){
    return mIndel;
}

void LeafData::setIndel(pair<int,int> posLength){
    mHasIndel=true;
    mIndel=posLength;
}

bool LeafData::isTrash(){
    return mIsTrash;
}

void LeafData::makeTrash(){
    mIsTrash=true;
}

bool LeafData::hasVariant(){//does this get used?
    return(mHasIndel || !mSubstitutions.empty());
}
