#include "HCNode.h"
#include "HCTree.h"
#include <fstream>
#include <stdlib.h>
#include <string>

/**
 * Name: Daniel Huang
 * Date: 2/14/2017
 * Assignment: PA3
 * Implementations that uncompress small files in plain ASCII
 */

int main(int argc, char* argv[]) {
    
    ifstream in;
    std::string str1(argv[1]);
    string infile=str1;
    std::string str2(argv[2]);
    string outfile=str2;
    
    //open the infile for reading
    in.open(infile);
    
    
    if ( in.peek() == std::ifstream::traits_type::eof() )
    {
        cout<<"The input file is empty"<<endl;
        return 0; //edge case (empty file)
    }
    
    std::vector<int> freqs= std::vector<int>(256);

    
    int nextInt=0;
    string mstring;
    for(int idx=0; idx<freqs.size();idx++) {
        
        getline(in,mstring);
        nextInt=stoi(mstring);
        if(in.eof())  break;
        
        freqs[idx]=nextInt; //populate the vector in order to recreate a tree
    }
    
       HCTree tree= HCTree();
    
    tree.build(freqs); //reconstruct the same Huffman Tree
    
    
    ofstream out;
    out.open(outfile);
    
    
    HCNode* curr=tree.getRoot();
    /*while(1) {
        nextInt=in.get()-'0';
        if(in.eof())  break;
        
        if(nextInt==1) {
            curr=curr->c1;
            if(tree.noChild(curr)){ //reach the leaf with symbol
                out<<curr->symbol; //write the sybol to output file
                curr=tree.getRoot(); //reset the curr point back to root
            }
        }
        else if(nextInt==0) {
            curr=curr->c0;
            if(tree.noChild(curr)){ //reach the leaf with symbol
                out<<curr->symbol; //write the sybol to output file
                curr=tree.getRoot(); //reset the curr point back to root
            }
        }
    }*/
    
    
    BitInputStream inBit = BitInputStream (in);
    
    int totalfreq = 0;
    for(int i=0; i<freqs.size(); i++) {
        
        totalfreq+= freqs[i];
    }
    int freq=0; //keep track of the added-up frequencies of all characters
    while(freq<totalfreq) {
        nextInt=inBit.readBit(); //read one bit at a time
        if(inBit.in.eof())  break;

        
        if(nextInt==1) {
            curr=curr->c1;
            if(tree.noChild(curr)){ //reach the leaf with symbol
                out<<curr->symbol; //write the sybol to output file
                freq++;
                curr=tree.getRoot(); //reset the curr point back to root
            }
        }
        else if(nextInt==0) {
            curr=curr->c0;
            if(tree.noChild(curr)){ //reach the leaf with symbol
                out<<curr->symbol; //write the sybol to output file
                freq++;
                curr=tree.getRoot(); //reset the curr point back to root
            }
        }
    }
    
    
    in.close();
    out.close();
    return 0;
}
