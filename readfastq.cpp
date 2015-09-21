#include <fstream>
string fname = "mrcaf-compressed-0.fastq";
    string hname = 'hist.txt';
    string gene = "rpob";
    string aligncheck = "TTCGGTTCCAGCCAGC";
    int alignshift = 5;
    ifstream readfile(fname);


    string line;
    Trie* trie = new Trie();
    while (getline(readfile, line))
    {
        istringstream iss(line);
        int throwthisout;
        string sequence;
        if (!(iss >> throwthisout >> sequence)){ break; }

        trie->addBarcode(sequence)

    }

