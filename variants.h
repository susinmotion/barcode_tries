#include "node.h"
#include <string>

int ** initializeHashMtx();

int hashSubstitutions (int pos, char nucleotide);

pair<int, char> unhashSubstitutions (int variantHash);

void checkVariants(string sequence, string target, LeafData* pCurrentData);


