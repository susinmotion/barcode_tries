#include "node.h"
#include <string>

int hashVariants (int pos, char nucleotide);

pair<int, char> unhashVariants (int variantHash);

void checkSubstitutions(string sequence, string target, Node* pCurrentNode, int ** ppHashMatrixPointer);


