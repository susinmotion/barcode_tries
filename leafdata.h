#ifndef LEAFDATA_H
#define LEAFDATA_H

#include <vector>
using namespace std;

class LeafData {
public:
    LeafData(int mCount = 0, bool mHasIndel=false, bool mIsTrash=false): mCount(mCount), mHasIndel(mHasIndel), mIsTrash(mIsTrash){};
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

private:
    int mCount;
    vector <int> mSubstitutions;
    bool mHasIndel;
    pair <int, int> mIndel;
    bool mIsTrash;
};
#endif
