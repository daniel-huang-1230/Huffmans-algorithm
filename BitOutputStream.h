#include <iostream>
#include <fstream>

/**
 * Name: Daniel Huang
 * Date: 2/18/2017
 * Assignment: PA3
 * Header file that contains constructors and function declarations
 */

class BitOutputStream {
private:
    char buf; //buffer(one byte)
    int nbits; //how many bits have been written to buf
    std::ostream& out; //reference to the output stram to use
    
public:
    //initialize a BitOutputStream that will use the given ostream
    // for output
    BitOutputStream(std::ostream& os) :out(os),buf(0),nbits(0) {
        //clear buffer and bit counter
    }
    
    void flush();
    
    void writeBit(int i);
    
};
