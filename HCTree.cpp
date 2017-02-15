#include "HCTree.h"
#include "HCNode.h"
#include <stack>
/**
 * Name: Daniel Huang
 * Date: 2/13/2017
 * Assignment: PA3
 * Implementations of all the methods in HCTree class
 */



/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
    

    //build a "forest" of single nodes for each non-zero count byte
    for(int i=0; i<freqs.size();i++) {
        if(freqs[i]!=0) {
            HCNode* p=new HCNode(freqs[i],i);
            this->queue().push(p); //push the pointer of node to the queue
        }
    }
    
    //loop while there are more than 1 tree in the forest
    while(this->queue().size()>1) {
        //popped two symbols with the lowest freqs
        HCNode* n1=this->queue().top();
        this->queue().pop();
        HCNode* n2=this->queue().top();
        this->queue().pop();
        
        //combine these two nodes to a new tree
        HCNode* n3= new HCNode(n1->count+n2->count,n1->symbol);
        
        n3->c0=n1;
        n3->c1=n2;
        n1->parent=n3;
        n2->parent=n3;
        
        //set the leaves vector to point to all leaf nodes
        if(this->noChild(n1)) {
            this->setLeaves(n1, n1->symbol);
        }
        if(this->noChild(n2)) {
            this->setLeaves(n2, n2->symbol);
        }
        
        //push the combined tree back to queue
        this->queue().push(n3);
    }
    
    //return the the final single big tree and point the root to it
    this->setRoot(this->queue().top());
    
    
}





/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree:: encode(byte symbol, ofstream& out) const {
    std::stack<char> stack;
    
    //traverse up until reaching the root
    while(this->getParent(this->getLeaves()[symbol])) {
        if(this->getLeaves()[symbol]==
           this->getParent(this->getLeaves()[symbol])->c0) {
            stack.push('0');
        }
        else if(this->getLeaves()[symbol]==
                this->getParent(this->getLeaves()[symbol])->c1) {
             stack.push('1');
        }
    }
    
    //reverse the sequence of bits
    while(!stack.empty()) {
        out<<stack.top();
        stack.pop();
    }
    
    
}

