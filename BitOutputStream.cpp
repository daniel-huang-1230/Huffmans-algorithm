#include "BitOutputStream.h"


/**
 * Name: Daniel Huang
 * Date: 2/10/2017
 * Assignment: PA3
 * The implementation of BitOutputStream methods
 */


/* Send the buffer to the output, and clear it
 */
int FULL=8; //to avoid magic number
void BitOutputStream:: flush() {
    out.put(buf); //write whatever in the buffer to output stream
    out.flush();
    buf=nbits = 0;
}

/* Write the least significant bit of the input argument to the bit buffer, and increment the bit buffer index.
 Will flush the buff FIRST if full
 */
void BitOutputStream:: writeBit(int i){
    
    //flush the buffer if it is full
    if(this->nbits==FULL) {
        this->flush();
    }
    int leastBit;
    
    //the least significant bit can only be 1 or 0
    if(i%2==0) {
        leastBit=0;
    }
    else {
        leastBit=1;
    }
    //use bitwise operations to write leastBit into the byte buffer
    buf = buf | ( leastBit<<(8-nbits-1));
    nbits++; //increment the number of bits that have been written
    
    
}
