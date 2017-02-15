#include "HCNode.h"
#include "HCTree.h"
#include <fstream>

/**
 * Name: Daniel Huang
 * Date: 2/14/2017
 * Assignment: PA3
 * Implementations that uncompress small files in plain ASCII
 */

int main(int argc, char* argv[]) {
    
    ifstream in;
    string infile=argv[1];
    string outfile=argv[2];
    
    
       //open the infile for reading
    in.open(infile);
    
    
    if ( in.peek() == std::ifstream::traits_type::eof() )
    {
        cout<<"The input file is empty"<<endl;
        
    }
    
    std::vector<int> freqs= std::vector<int>(256);

    int nextInt=0;
    
    for(int idx=0; idx<freqs.size();idx++) {
        in>>nextInt;
        if(in.eof()) {
            cout<<"The file header is incomplete!"<<endl;
            break;
            
        }
        freqs[idx]=nextInt; //populate the vector in order to  recreate a tree
    }
    
    HCTree tree= HCTree();
    
    tree.build(freqs); //reconstruct the Huffman Tree
    
    
    return 0;
}
