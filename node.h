#include <iostream>
#include <vector>
using namespace std;


class Node {
public:
    Node();
    ~Node();
    char content();
    void setContent(char c);
    int count();
    void setCount();
    Node* findChild(char c);
    void appendChild(Node* child);
    vector<Node*> children();

private:
    char mContent;
    int mCount;
    vector<Node*> mChildren;
};
