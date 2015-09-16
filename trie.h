class Trie {
public:
    Trie();
    ~Trie();
    void addBarcode(string s);
    int outputBarcodeCount(string s);
private:
    Node* root;
};
