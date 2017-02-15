#include "HCTree.h"
#include "HCNode.h"
#include <stack>
/**
 * Name: Daniel Huang
 * Date: 2/13/2017
 * Assignment: PA3
 * Implementations of all the methods in HCTree class
 */

/** the destructor
 **/
HCTree::  ~HCTree(){
    
    deleteAll(root);
}

/**do a postorder traversal, deleting all nodes
 **/
void HCTree:: deleteAll(HCNode* p) {
    if(!p) {
        return ;
    }
    
    deleteAll(p->c0);
    
    deleteAll(p->c1);
    
    delete p;
}

/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
    
    // the priority queue to store our nodes, with the overloaded compare class
    std::priority_queue <HCNode*,std::vector<HCNode*>, HCNodePtrComp> pq;
    
    //build a "forest" of single nodes for each non-zero count byte
    for(int i=0; i<freqs.size();i++) {
        if(freqs[i]!=0) {
            HCNode* p=new HCNode(freqs[i],(unsigned char)i);
            pq.push(p); //push the pointer of node to the queue
            
        }
    }
    
    
    
    //loop while there are more than 1 tree in the forest
    while(pq.size()>1) {
        //popped two symbols with the lowest freqs
        HCNode* n1=pq.top();
        pq.pop();
        
        HCNode* n2=pq.top();
        pq.pop();
        
        //combine these two nodes to a new tree
        HCNode* n3= new HCNode(n1->count+n2->count,n1->symbol);
        
        
        //set the leaves vector to point to all leaf nodes
        if(this->noChild(n1)) {
            this->setLeaves(n1, n1->symbol);
        }
        if(this->noChild(n2)) {
            this->setLeaves(n2, n2->symbol);
        }
        
        n3->c0=n1;
        n3->c1=n2;
        n1->parent=n3;
        n2->parent=n3;
        
        
        
        //push the combined tree back to queue
        pq.push(n3);
        //update the root
        
    }
    
    this->setRoot(pq.top());
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
    
    HCNode* curr=this->getLeaves()[symbol];
    //traverse up until reaching the root
    while(curr->parent) {
        if(curr==curr->parent->c0) {
            stack.push('0');
        }
        else if(curr==curr->parent->c1) {
            stack.push('1');
        }
        curr=curr->parent; //advance the curr pointer
    }
    
    
    //reverse the sequence of bits and write it to the output file
    while(!stack.empty()) {
        out<<stack.top();
        stack.pop();
    }
    
}


/** Return the symbol coded in the next sequence of bits (represented as
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */
int HCTree:: decode(ifstream& in) const {
    
    
    return 0;
}

