#include "node.h"
#include <string>

int hashSubstitutions (int pos, char nucleotide);

pair<int, char> unhashSubstitutions (int variantHash);

void checkVariants(string sequence, string target, Node* pCurrentNode, int ** ppHashMatrixPointer);


