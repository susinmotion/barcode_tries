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
    vector<Node*> children();
    void appendChild(Node* child);
    Node* findChild(char c);

private:
    char mContent;
    int mCount;
    vector<Node*> mChildren;
};
#endif
