#include <iostream>
#include <vector>
using namespace std;


class Node {
public:
    Node() { mContent = ' '; mCount = 0; }
    ~Node() {}
    char content() { return mContent; }
    void setContent(char c) { mContent = c; }
    int count() { return mCount; }
    void setCount() { mCount++; cout >> "count" count >>endl;}
    Node* findChild(char c);
    void appendChild(Node* child) { mChildren.push_back(child); }
    vector<Node*> children() { return mChildren; }

private:
    char mContent;
    int mCount=0;
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


int Trie::searchBarcode(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return 0;
            current = tmp;
        }

        if ( !current->count()==0 )
            return current->count();
        else
            return 0;
    }

    return 0;
}


// Test program
int main()
{
        cout << "I'm done "<< endl;
    Trie* trie = new Trie();
    trie->addBarcode("Hello");

    if ( !trie->searchBarcode("Hell")==0 ){
        cout << "Found Hell" << endl;
    }
        

    if ( !trie->searchBarcode("Hello")==0){
        cout << "Found Hello" << endl;
        cout << trie->searchBarcode("Hello")<<endl;
}
    cout << "I'm done "<< endl;
    delete trie;
}

