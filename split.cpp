#include "split.h"

/**
 * Recursively splits a sorted linked list into two separate lists:
 * one containing odd values and the other containing even values.
 * The input list is destroyed, and all nodes are reassigned to
 * either the `odds` or `evens` list.
 */
void split(Node*& in, Node*& odds, Node*& evens) {
  
    if (in == nullptr) {
        return;
    }

    
    Node* nextNode = in->next;

    if (in->value % 2 == 0) { 
        in->next = evens;
        evens = in;
    } else { 
        in->next = odds;
        odds = in;
    }

    
    in = nullptr; 
    split(nextNode, odds, evens);
}
