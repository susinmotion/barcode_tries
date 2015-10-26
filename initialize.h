#include "trie.h"
#include <map>
#include <string>

map <string, int> readConfig(string filename);
int ** initializeHashMtx();
void readFileIntoTrie(Trie* trie, string filename);
