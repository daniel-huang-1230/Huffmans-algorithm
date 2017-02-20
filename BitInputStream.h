#include <iostream>
#include <fstream>


/**
 * Name: Daniel Huang
 * Date: 2/18/2017
 * Assignment: PA3
 * Header file that contains constructors and function declarations
 */

//int EMPTY=8;
class BitInputStream{
private:
    char buf; //buffer(one byte)
    int nbits; //how many bits have been read from buf
    

    
    
public:
    //istream declared as public so that we can check EOF
    std::istream& in; //reference to the input stram to use
    BitInputStream(std::istream& is): in(is), buf(0) {
        
        
        nbits = 8; //initialized as 8 , need to be filled first
    }
  
    void fill();
    
    int readBit();
    
    
};
