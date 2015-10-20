#ifndef NODE_H
#define NODE_H

#include <typeinfo>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Node {
public:
/*    Node(){};
    Node(Node* original){
      
      mVariants=original->mVariants;
      mContent=original->mContent;
      mCount=original->mCount;

      for (int i = 0; i < original->children().size(); ++i) {
           Node* temp = new Node(); 
           temp = original->children()[i]; 
           mChildren[i] = temp;
           cout<<typeid(mChildren[i]).name()<<"type of mchildren i"<<endl;
           cout<<typeid(temp).name()<<"type temp"<<endl;
        }
     cout<<"copy constructor got called"<<endl;
    }
    Node operator= (Node other){
        cout<<"assignment operator called start"<<endl;
      //  swap(mVariants, other.mVariants); 
       // cout<<"swapping variants"<<endl;
//        swap(mChildren, other.mChildren);
  //      cout<<"swapping children"<<endl; 
        mCount=2;
//other.count(); 
   //     mContent= other.content(); 
        cout<<"assignment operator got called"<<endl;
        return this;
    }*/
    char content();
    void setContent(char c);
    int count();
    void setCount();
    vector <int> substitutions();
    void appendSubstitution(int substitution);
    void replaceSubstitutions(vector<int>substitutions);
    bool hasIndel();
    pair <int, int> indel();
    void setIndel(pair<int, int>posLength);
    bool isTrash();
    void makeTrash();
    bool hasVariant();
    vector<Node*> children();
    void appendChild(Node* child);
    Node* findChild(char c);

private:
    char mContent;
    int mCount;
    vector <int> mSubstitutions;
    bool mHasIndel;
    pair <int, int> mIndel;
    bool mIsTrash;
    vector<Node*> mChildren;
};
#endif
