#ifndef NODE_H
#define NODE_H

#include <vector>
#include "leafdata.h"
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
    vector<Node*> children();
    void appendChild(Node* child);
    Node* findChild(char c);
    void initializeLeafData(int numberOfROIs, int numberOfPhases);
    vector <vector<LeafData*> > leafData();
    void setLeafData(int ROINumber, int phase, LeafData* data);

private:
    char mContent;
    vector<Node*> mChildren;
    vector <vector<LeafData*> > mLeafData;
};
#endif
