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
    BitOutputStream outBit=BitOutputStream(out);
    
    out.open(outfile); //open the output file for writing
    
    char bufArray[2048];
    for(int i=0; i<2048; i++){
        bufArray[i]=NULL;
    }
    
     for(int i=0; i<freqs.size();i++) {
     //out<<freqs[i]<<"\n";  //write 256 ints in the header portion
         
         //try to encode the header in a more efficient manner,
        
         if(freqs[i]!=0){
             char c= freqs[i]+'0';
             char idx=i+'0';
             int j=0;
             while(bufArray[j]!=NULL) {
                 j++; //find a empty index to insert
             }
             bufArray[j]=c;
             
             bufArray[j+1]=idx;
             
            //out<<freqs[i]<<"\n";
             //out<<i<<"\n"; //the index
         
         }
     }
    for(int i=0; i<2048;i++){
        if(bufArray[i]!=NULL){
            int byte=(int)bufArray[i]-'0';
            
            out<<byte<<"\n";
           
        }
        
    }
    
         out<<-1<<"\n"; //denote the end of header
    
  
   /* HCNode* curr= tree.getRoot();
    int totalfreq=0;
    
    for(int i=0; i<freqs.size();i++) {
        if(freqs[i]!=0){
            totalfreq+=freqs[i];
        }
    }
    int symbolNum=0;
    
    for(int i=0; i<tree.getLeaves().size(); i++) {
        if(tree.getLeaves()[i]!=0) {
            symbolNum++;
        
        }
    }
  
    out<<symbolNum<<"\n";  //write the total number of distinct symbols to first line
    
    out<<totalfreq<<"\n"; //record the total frequency on the second line
    
    tree.writeHeader(curr, out); //record the structure of the tree in header!!
    
    */
    
    in.open(infile); //open the input file again and read
    
    
    //write the code for each symbol(letter) in the file
    
    char nextChar;
    
    
    while(1){
        nextChar=(unsigned char)in.get();
        if(in.eof()) break;
        
        //tree.encode(nextChar,out);
        tree.encode(nextChar, outBit);
    }
    outBit.flush(); //flush everything in the buffer to write to ostream
    
    
    
    // Close both the input and output files
    out.close();
    
    in.close();
    
    cout<<"File compressed!"<<endl;
    return 0;
}
