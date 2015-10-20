#include "variants.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

string nucleotides = "ACGTN";

int ** initializeHashMtx(){//cols 0-4 represent bases ACGTN, in that order. Rows represent position of variant.
    int maxSequenceLength=400;
    int ** ppHashMatrixPointer = new int*[maxSequenceLength];
    short int count=0;
    for (int row = 0; row < maxSequenceLength; row++){
        ppHashMatrixPointer[row]=new int[5];
        for (int col = 0; col < 5; col++){
            *(* (ppHashMatrixPointer+row)+col) = count;
            count++;
        }
    }
    return ppHashMatrixPointer;
}

int ** ppHashMatrixPointer = initializeHashMtx();

int hashSubstitutions (int pos, char nucleotide){//hash pos/nucleotide to int
    int nucleotidePos = nucleotides.find(nucleotide);
    int variantHash =*(*(ppHashMatrixPointer+pos)+nucleotidePos);
    return variantHash;
}

pair<int, char> unhashSubstitutions (int variantHash){//unhash int into pos/nucleotide
    int nucleotidePos = variantHash % 5;
    char nucleotide = nucleotides.at(nucleotidePos);
    int pos = (variantHash - nucleotidePos) / 5;
    return pair<int, char>(pos, nucleotide);
}

void checkVariants(string sequence, string target, Node* pCurrentNode){
    int variantPos;
    vector <int> currentSubstitutions;
    for (int i=0; i<(min(sequence.length(), target.length())); ++i){
        if ( sequence[i]!=target[i] ){//check to see if the sequence differs from the target
            variantPos = i;
            if ( sequence.length()!=target.length() ){//if the sequence is longer or shorter than expected mark indel
                int indelLength=sequence.length()-target.length();
                pair <int,int> indel=make_pair(variantPos, indelLength);

                if ( (pCurrentNode->count()>0) && (pCurrentNode->indel()!=indel) ){//if there's been a read before that doesn't match the indel found, trash all reads from this barcode
                    pCurrentNode->makeTrash();
                }
                else{
                    pCurrentNode->setIndel(indel);
                }
                return;
            }

            else{
                if ( pCurrentNode->hasIndel() ){//if we are getting a substitution and we had an indel before, trash
                    pCurrentNode->makeTrash();
                return;
                }
                int substitutionHash = hashSubstitutions(variantPos, sequence[variantPos]);
                currentSubstitutions.push_back(substitutionHash);
            }      
        }
    }
    if (currentSubstitutions.size()!=0){
        pCurrentNode->replaceSubstitutions(currentSubstitutions);
    }
}
