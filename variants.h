#include "node.h"
#include <string>

int hash_variants (int pos, char nucleotide);

pair<int, char> unhash_variants (int variant_hash);

void check_substitutions(string sequence, string target, Node* current, int ** hash_matrix_pointer);


