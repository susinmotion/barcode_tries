#include "trie.h"
#include <map>
#include <string>
#include <vector>

map <string, vector <string> > readConfig(string filename);
int ** initializeHashMtx();
vector <Trie*> readFileIntoTrie(string filename);
