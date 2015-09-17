nclude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifstream>
#include <fstream>
#include <ofstream>

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
        index = CHAR_TO_INDEX(key[level]);
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
 
int char_to_index(char c)
{   
    int index;

    if (c=="a")
    {
        index=0;
    }
    if (c=="c")
    {
        index=1;
    }
    if (c=="t")
    {
        index=2;
    }
    if (c=="g")
    {
        index=3;
    } 
    return index;
}


void print_trie(trie_pointer *pTrie)
{

    trie_node_t *nodePointer;
    nodePointer = pTrie->root;
    char key[14];
    char *keyPointer;
    keyPointer = key; 
    ofstream outputfile("output.txt")
    //create pointer to array

    for (level=0; level<14; level++){

        for (i=0; i<ALPHABET_SIZE; i++){
           
            if (!nodePointer->children[i] == NULL){
                key[i]= *children[i];
                keyPointer = keyPointer++;
                *nodePointer = children[i]
            }
//this section needs to come out so we can recurse properly.
            //make sure variables are handled by reference properly
    }
    if (!nodePointer->value==0){
        if (outputfile.is_open()) 
        { 
        outputfile >> key >> " " >> value 
        }
    }
    outputfile.close()

    //pointer to root and pointer to the start of this array

    //append child to array 
    //make the pointer point to the child
    //make the array pointer point to next
    //recurse
    //if a node has a value, print the array and the value
}
int main()
{
    string fname = "mrcaf-compressed-0.fastq";
    string hname = 'hist.txt';
    string gene = "rpob";
    string aligncheck = "TTCGGTTCCAGCCAGC";
    int alignshift = 5;
    ifstream readfile(fname);


    string line;

    trie_t trie;
    initialize(&trie);

    while (getline(readfile, line))
    {
        istringstream iss(line);
        int throwthisout;
        string sequence;
        if (!(iss >> throwthisout >> sequence)){ break; }

        insert(&trie, sequence)

    }

    return trie;
}
