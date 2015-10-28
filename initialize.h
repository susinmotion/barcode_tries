#include "trie.h"
#include <map>
#include <string>
#include <vector>

string reverseComplement(string);
map <string, vector <string> > readConfig(string filename);
int ** initializeHashMtx();
vector <Trie*> readFileIntoTrie(string filename);
