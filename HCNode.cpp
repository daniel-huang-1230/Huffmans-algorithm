#include "HCNode.h"

/**
 * Name: Daniel Huang
 * Date: 2/10/2017
 * Assignment: PA3
 * Implementations of methods in HCNode class
 */


//Compare this node and other for priority ordering
//overload the "<" operator so that lower count would have
//higher priority in the priority queue
bool HCNode:: operator < (const HCNode& other) {
    //if counts are different, just compare counts
    if(this->count!=other.count) {
        return this->count > other.count;
    }
    // if counts are equal, we need to break tie deterministically
    // here I'll use the ASCII values of the symbols in two nodes
    // character with smaller value has LOWER priority
    return this->symbol < other.symbol;
}
