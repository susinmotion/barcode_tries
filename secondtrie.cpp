#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "node.h"
#include "trie.h"
using namespace std;

void read_file_into_trie(Trie* trie){
cout<<"hi!!"<<endl;
	string fname = "shorter.fastq";
	//string hname = "hist.txt";
//	string gene = "rpob";
int count=0;    
//	string aligncheck = "TTCGGTTCCAGCCAGC";
//	int alignshift = 5;
	ifstream readfile (fname.c_str());


    	string barcode;
	int throwout;
	string throwoutstring;
	if (readfile.is_open())
{ cout<<"file isopen"<<endl;
getline(readfile,barcode);
cout<<barcode<<endl;
 	   while (readfile>>throwout)
    		{
		count++;
		readfile>>barcode;
		if (barcode.find("N")==-1){
	
		cout<<barcode<<" "<<count<<endl;        	
	/*	istringstream iss(line);
        	int throwthisout;
        	string sequence;
        	if (!(iss >> sequence>> throwthisout)){ break; }
*/
      		trie->addBarcode(barcode);
		}
readfile>>throwoutstring;
    	
		
	}
}
}

int return_max_count(Node* current, int& max )
{

        vector <Node*> children = current->children();
        if (!children.empty()){

                for (int i=0; i<children.size(); i++){

                        current = children[i];
                        return_max_count(current, max);
                }
        }
        else if((current->count()!=0) && (current->count()>max) ){
	max&=current->count();
	//I'm leaving off here! I am not passing by reference/value properly. current->count() is right, but max isn't/isn't being passed correctly
cout<<current->count()<<endl;
	return max;
}
return max;
}




void print_trie(Node* current, string outputString=string(1000,'\0'), int index = 0)
{
        outputString[index] = current->content();
        vector <Node*> children = current->children();
        if (!children.empty()){

                for (int i=0; i<children.size(); i++){

                        current = children[i];
			index++;
                        print_trie(current, outputString, index);
                }
        }
	else if(current->count()!=0){
cout<<"Barcode "<<outputString<<" was found "<<current->count()<<" times."<<endl;
return;
}
}

int main()
{
    Trie* trie = new Trie();
    
    trie->addBarcode("Hello");
    trie->addBarcode("TestingMore");
    trie->addBarcode("TestingMore");
    trie->addBarcode("TestingMore");
    trie->addBarcode("SomeMoreString");
    trie->addBarcode("Thisissuperlong");
    trie->outputBarcodeCount("Hell");    
    trie->outputBarcodeCount("Thisissuperlonghowillyouprint,huh?");
    trie->outputBarcodeCount("Hello");
    trie->outputBarcodeCount("Hellow");    

    Trie* trie2 = new Trie();
    trie2->outputBarcodeCount("testing");

Node* current = trie->root();
    cout<<"printing the trie"<<endl<<endl;
    print_trie(current);

    read_file_into_trie(trie2);
    current= trie2->root();
    // print_trie(current);
int max=0;
max=return_max_count(current, max);
cout<<max<<" is the max."<<endl;    
cout << "I'm done "<< endl;
    delete trie;
}

