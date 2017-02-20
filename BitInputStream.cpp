#include "BitInputStream.h"



/**
 * Name: Daniel Huang
 * Date: 2/10/2017
 * Assignment: PA3
 * The implementation of BitInputStream methods
 */


/*Fill the buffer from the input
 */
void BitInputStream:: fill() {
    
    buf=in.get();
    nbits=0;
}


/* Read the next bit from the bit buffer.
   Fill the buffer from the input stream first if buf is empty
   Return 1 if the bit read is 1;
   Return 0 if the bit read is 0;
 */
int BitInputStream:: readBit() {
    if(this->nbits==8) {
        this->fill();  //fill the buf first if it's empty(all bits are read)
    }
    
    int leftmost = buf>>(8-nbits-1);
    nbits++; //increment the index

    if(leftmost%2==0) {
        return 0;
    }
    else {
        return 1;
    }
   }
