#include <iostream>
#include <vector>
using namespace std;

#define ALPHABET_SIZE 4

class Node {
public:
    Node() { mContent = ' '; mCount = 0; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    int count() { return mCount; }
    void setCount() { mCount++;}
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    int mCount;
    vector<Node*> mChildren;
};

class Trie {
public:
    Trie();
    ~Trie();
    void addBarcode(string s);
    bool searchBarcode(string s);
    void deletBarcode(string s);
private:
    Node* root;
};

Node* Node::findChild(char c)
{
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addBarcode(string s)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->setCount(); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {        
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->setCount();
    }
}


bool Trie::searchBarcode(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return false;
            current = tmp;
        }

        if ( !current->count()==0 )
            return true;
        else
            return false;
    }

    return false;
}


// Test program
int main()
{
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    if ( trie->searchBarcode("Hell") )
        cout << "Found Hell" << endl;

    if ( trie->searchBarcode("Hello") )
        cout << "Found Hello" << endl;


    delete trie;
}

