#ifndef NODE_H
#define NODE_H

#include <vector>
using namespace std;

class Node {
public:
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
#endif
