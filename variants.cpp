#include "variants.h"
#include <vector>
#include <string>

using namespace std;

int hash_variants (int pos, char nucleotide, int *(hash_matrix_pointer)[5]){
    string nucleotides = "ACGTN";
    int nucleotide_pos = nucleotides.find(nucleotide);
    int variant_hash =*(*(hash_matrix_pointer+pos)+nucleotide_pos);
    return variant_hash;
}

pair<int, char> unhash_variants (int variant_hash){
    string nucleotides = "ACGTN";
    int nucleotide_pos = variant_hash % 5;
    char nucleotide = nucleotides.at(nucleotide_pos);
    int pos = (variant_hash - nucleotide_pos) / 5;
    return pair<int, char>(pos, nucleotide);
}

void check_substitutions(string sequence, string target, Node* current, int ** hash_matrix_pointer){
    for (int i =0; i<target.length(); i++){
        if (sequence[i]!=target[i]){
            current->appendVariant(hash_variants(i, sequence[i], hash_matrix_pointer));
        }
    }
}
