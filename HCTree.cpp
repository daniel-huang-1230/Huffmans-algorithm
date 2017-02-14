#include "HCTree.h"
#include "HCNode.h"

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
void build(const vector<int>& freqs){
    
    HCTree tree= HCTree();
    //build a "forest" of single nodes for each non-zero count byte
    for(int i=0; i<freqs.size();i++) {
        if(freqs[i]!=0) {
            HCNode* p=new HCNode(freqs[i],i);
            tree.queue().push(p); //push the pointer of node to the queue
        }
    }
    
    //loop while there are more than 1 tree in the forest
    while(tree.queue().size()>1) {
        //popped two symbols with the lowest freqs
        HCNode* n1=tree.queue().top();
        tree.queue().pop();
        HCNode* n2=tree.queue().top();
        tree.queue().pop();
        
        //combine these two nodes to a new tree
        HCNode* n3= new HCNode(n1->count+n2->count,n1->symbol);
        
        n3->c0=n1;
        n3->c1=n2;
        n1->parent=n3;
        n2->parent=n3;
        
        //set the leaves vector to point to all leaf nodes
        if(n1->c0==0 && n1->c1==0) {
            tree.setLeaves(n1, n1->symbol);
        }
        if(n2->c0==0 && n2->c1==0) {
            tree.setLeaves(n2, n2->symbol);
        }
        
        //push the combined tree back to queue
        tree.queue().push(n3);
    }
    
    //return the the final single big tree and point the root to it
    tree.setRoot(tree.queue().top());
    
    
}
