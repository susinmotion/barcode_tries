#include "node.h"
#include <string>

int hash_variants (int pos, char nucleotide, int (*hash_matrix)[5]);

pair<int, char> unhash_variants (int variant_hash);
void check_substitutions(string sequence, string target,  int (*hash_matrix)[5], Node* current);


