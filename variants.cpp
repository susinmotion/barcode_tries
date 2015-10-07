#include "variants.h"
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
                pCurrentNode->setIndel(indelLength, i);
            }
        }
    }
    else{
        for (int i =0; i<target.length(); i++){
            if (sequence[i]!=target[i]){
                
                pCurrentNode->appendSubstitution(hashSubstitutions(i, sequence[i], ppHashMatrixPointer));
            }
        }
    }
}
