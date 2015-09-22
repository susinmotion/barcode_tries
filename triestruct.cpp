#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE 4
// Alphabet size (# of symbols)
//#define ALPHABET ["a","c","t","g"]
// Converts key current character into index
// use only 'a' through 'z' and lower case
//#define CHAR_TO_INDEX(c) ALPHABET[((int)c - (int)'a')]

// trie node
//a node is a value with an instance of a trie that consists of an array of up to 4 pointers to children



typedef struct trie_node trie_node_t;
struct trie_node
{
    int value;
    trie_node_t *children[ALPHABET_SIZE];
};
 
// trie ADT
//a trie is a node with a pointer to a root, and a count
typedef struct trie trie_t;
struct trie
{
    trie_node_t *root;
    int count;
};
 
// Returns new trie node (initialized to NULLs)
trie_node_t *getNode(void)
{
    trie_node_t *pNode = NULL;
 
    pNode = (trie_node_t *)malloc(sizeof(trie_node_t));
 
    if( pNode )
    {
        int i;
 
        pNode->value = 0;
 
        for(i = 0; i < ALPHABET_SIZE; i++)
        {
            pNode->children[i] = NULL;
        }
    }
 
    return pNode;
}
int char_to_index(char c)
{
    int index;

    if (c=='a')
    {
        index=0;
    }
    if (c=='c')
    {
        index=1;
    }
    if (c=='t')
    {
        index=2;
    }
    if (c=='g')
    {
        index=3;
    }
    return index;
}
 
// Initializes trie (root is dummy node)
void initialize(trie_t *pTrie)
{
    pTrie->root = getNode();
    pTrie->count = 0;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *nodePointer;
 
    //pTrie->count++;
    nodePointer = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
       //this should become a map of keys to indices
        index = char_to_index(key[level]);
        if( !nodePointer->children[index] )
        {
            nodePointer->children[index] = getNode();
        }
 
        nodePointer = nodePointer->children[index];
    }
 
    // mark last node as leaf
    nodePointer->value++;
}
 
// Returns non zero, if key presents in trie
int search(trie_t *pTrie, char key[])
{
    int level;
    int length = strlen(key);
    int index;
    trie_node_t *nodePointer;
 
    nodePointer = pTrie->root;
 
    for( level = 0; level < length; level++ )
    {
        index = char_to_index(key[level]);
 
        if( !nodePointer->children[index] )
        {
            return 0;
        }
 
        nodePointer = nodePointer->children[index];
    }
 
    return (0 != nodePointer && nodePointer->value);
}

int main(){
trie t= new trie;
trie *ptrie = t;
initialize(ptrie);
return 0;
}

