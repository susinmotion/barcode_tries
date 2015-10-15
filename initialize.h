#include "trie.h"
#include <map>
#include <string>

map <string, int> readConfig();
int ** initializeHashMtx();
//int BARCODE_LENGTH;
int outputBarcodeLength();
void readFileIntoTrie(Trie* trie);
