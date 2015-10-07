#include "variants.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int hashSubstitutions (int pos, char nucleotide, int *(ppHashMatrixPointer)[5]){
    string nucleotides = "ACGTN";
    int nucleotidePos = nucleotides.find(nucleotide);
    int variantHash =*(*(ppHashMatrixPointer+pos)+nucleotidePos);
    return variantHash;
}

pair<int, char> unhashSubstitutions (int variantHash){
    string nucleotides = "ACGTN";
    int nucleotidePos = variantHash % 5;
    char nucleotide = nucleotides.at(nucleotidePos);
    int pos = (variantHash - nucleotidePos) / 5;
    return pair<int, char>(pos, nucleotide);
}

void checkVariants(string sequence, string target, Node* pCurrentNode, int ** ppHashMatrixPointer){
    if (sequence.length()!=target.length()){
        int indelLength=sequence.length()-target.length();
        for (int i=0; i<(min(sequence.length(), target.length())); ++i){
            if (sequence[i]!=target[i]){
                pair <int,int> indel=make_pair(i, indelLength);
                if (pCurrentNode->hasIndel()==false){
                    pCurrentNode->setIndel(indel);
                }
                else if (pCurrentNode->indel()!=indel){ //DUMP
                }
            }
        }
    }
    else{
        vector <int> confirmedSubstitutions;
        vector <int> existingSubstitutions=pCurrentNode->substitutions();
        
        for (int i =0; i<target.length(); i++){
            if (sequence[i]!=target[i]){
                int substitutionHash = hashSubstitutions(i, sequence[i], ppHashMatrixPointer);
                if( (pCurrentNode->count()>1) && 
                  (find(existingSubstitutions.begin(), existingSubstitutions.end(), substitutionHash)==existingSubstitutions.end())){
                  substitutionHash=(substitutionHash/5)*5+4;
                }
                confirmedSubstitutions.push_back(substitutionHash);
            }
        }
        pCurrentNode->replaceSubstitutions(confirmedSubstitutions);
    }
    
}
