#include "variants.h"
#include <vector>
#include <string>

using namespace std;

int hashVariants (int pos, char nucleotide, int *(ppHashMatrixPointer)[5]){
    string nucleotides = "ACGTN";
    int nucleotidePos = nucleotides.find(nucleotide);
    int variantHash =*(*(ppHashMatrixPointer+pos)+nucleotidePos);
    return variantHash;
}

pair<int, char> unhashVariants (int variantHash){
    string nucleotides = "ACGTN";
    int nucleotidePos = variantHash % 5;
    char nucleotide = nucleotides.at(nucleotidePos);
    int pos = (variantHash - nucleotidePos) / 5;
    return pair<int, char>(pos, nucleotide);
}

void checkSubstitutions(string sequence, string target, Node* pCurrentNode, int ** ppHashMatrixPointer){
    for (int i =0; i<target.length(); i++){
        if (sequence[i]!=target[i]){
            pCurrentNode->appendVariant(hashVariants(i, sequence[i], ppHashMatrixPointer));
        }
    }
}
