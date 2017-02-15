#include "HCNode.h"
#include "HCTree.h"
#include <fstream>

/**
 * Name: Daniel Huang
 * Date: 2/14/2017
 * Assignment: PA3
 * Implementations that compress small files in plain ASCII
 */

int main(int argc, char* argv[]) {
    
    
    ifstream in;
    string infile=argv[1];
    string outfile=argv[2];
    
    in.open(infile); //open the file
    
    std::vector<int> freqs= std::vector<int>(256); //create a vector to keep track of the counts
    
    int nextInt=0;
    
    while(1) {
        
        nextInt=in.get();
        if(in.eof()) break;
        
        freqs[nextInt]+=1; //count the occurence of every byte
        
    }
    
    in.close(); //close the input file
    
    HCTree tree= HCTree();
    
    tree.build(freqs); //build the Huffman Tree
    
    ofstream out;
    
    out.open(outfile); //open the output file for writing
    
    for(int i=0; i<freqs.size();i++) {
        
        out<<freqs[i]<<"\n";  //write 256 ints in the header portion
        //one per line
    }
    
    in.open(infile); //open the input file again
    
    
    //write the code for each symbol(letter) in the file
    for(int i=0; i<tree.getLeaves().size();i++) {
        if(tree.getLeaves()[i]->count!=0) {
            tree.encode(tree.getLeaves()[i]->symbol,out);
        }
    }
    
    // Close both the input and output files
    out.close();
    in.close();
    
    return 0;
}
