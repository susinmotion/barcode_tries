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
                /*if (!pCurrentNode->hasVariant()){//if there's not already a variant,add this variant to temp vector
                  // pCurrentNode->appendSubstitution(substitutionHash);
                   confirmedSubstitutions.push_back(substitutionHash);
                }
                else{
                    int posInExisting= find(existingSubstitutions.begin(), existingSubstitutions.end(), substitutionHash);
                    if (posInExisting!=existingSubstitutions.end()){ //if the same variant is already there, add it to the list
                        confirmedSubstitutions.push_back(substitutionHash);
                       // existingSubstitutions.erase(posInExisting);//and remove from existing list
                    }
                    else{ //if that variant isn't already there, it's uncertain. mark it as an N
                        substitutionHash=(substitutionHash/5)+4;
                        confirmedSubstitutions.push_back(substitutionHash);
                    }
                }
*/                cout<<substitutionHash<<endl;
                if( (pCurrentNode->count()>1) && (find(existingSubstitutions.begin(), existingSubstitutions.end(), substitutionHash)==existingSubstitutions.end())){
                  cout<<substitutionHash<<endl; 
                  substitutionHash=(substitutionHash/5)*5+4;
                   cout<<substitutionHash<<endl;
                }
                confirmedSubstitutions.push_back(substitutionHash);
            }
        }
        pCurrentNode->replaceSubstitutions(confirmedSubstitutions);
    }
    
}
