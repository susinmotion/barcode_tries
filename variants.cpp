#include "variants.h"
#include <vector>
#include <string>
using namespace std;

int hash_variants (int pos, char nucleotide){
    string nucleotides = "ACGTN";
    int nucleotide_pos = nucleotides.find(nucleotide);
    cout << "found nucleotide at" <<pos <<" "<<nucleotide_pos<<endl;
    int variant_hash =hash_matrix[pos][nucleotide_pos];
    cout <<variant_hash<<endl;
    return variant_hash;
}

pair<int, char> unhash_variants (int variant_hash){
    string nucleotides = "ACGTN";
    int nucleotide_pos = variant_hash % 5;
    char nucleotide = nucleotides.at(nucleotide_pos);
    int pos = (variant_hash - nucleotide_pos) / 5;
    return pair<int, char>(pos, nucleotide);
}
vector<int> check_substitutions(string sequence, string target){
    vector<int> substitutions;
    for (int i =0; i<target.length(); i++){
        if (sequence[i]!=target[i]){
            substitutions.push_back(hash_variants(i, sequence[i]));
        }
    }
    return substitutions;
}
