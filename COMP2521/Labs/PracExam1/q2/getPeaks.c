// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

DLList getPeaks(DLList L){
    
    // new list for peaks
	DLList peaksL = newDLList();
   
    if (DLListLength(L) < 3) {
        return peaksL;
    }

    DLListNodeP curr = L->first->next;
    
    while (curr->next != NULL) {
        // if curr is a peak
        if (curr->value > curr->next->value && curr->value > curr->prev->value) {
            // make new node
            DLListNodeP new = newDLListNode(curr->value);
            // first node
            if (peaksL->nitems == 0) {
                peaksL->first = new;
                peaksL->last = new;
                peaksL->nitems++;
            }
            // add node at end  
            else {
                peaksL->last->next = new;
                new->prev = peaksL->last;
                peaksL->last = new;
                peaksL->nitems++;
            }
        }
        curr = curr->next;
    }
    
	return peaksL;
}



