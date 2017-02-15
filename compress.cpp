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
    std::string str1(argv[1]);
    string infile=str1;
    std::string str2(argv[2]);
    string outfile=str2;
    
    in.open(infile); //open the file
    
    if ( in.peek() == std::ifstream::traits_type::eof() )
    {
        cout<<"The input file is empty"<<endl;
        return 0;  //return w/o creating a Huffman Trees
    }
    
    std::vector<int> freqs= std::vector<int>(256,0); //create a vector to keep track of the counts
    
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
    
    in.open(infile); //open the input file again and read
    
    
    //write the code for each symbol(letter) in the file

    char nextChar;
    while(1) {
        nextChar=(unsigned char)in.get();
        if(in.eof()) break;
        
        tree.encode(nextChar,out);
        
    }
    // Close both the input and output files
    out.close();
    
    in.close();  
    
 
    return 0;
}
