// removeValue.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"

void removeValue(DLList L, int value){
    assert(L->nitems != 0);
    
    // Store current node
    DLListNodeP temp = L->first, prev = NULL;
 
    // If first node itself holds the key or multiple occurrences of key
    while (temp != NULL && temp->value == value)
    {
        if(temp->next == NULL)
        {
            free(temp);
            L->first = NULL;
            L->last = NULL;
            L->curr = NULL;
            L->nitems--;
            return;
        }
        temp = temp->next;  
        free(temp->prev);
        L->first = temp;
        L->nitems--;
        temp->prev = NULL; 
    }
 
    // Delete occurrences other than first
    while (temp != NULL)
    {
        // Search for the key to be deleted, keep track of the
        // previous node as we need to change 'prev->next'
        while (temp != NULL && temp->value != value)
        {
            prev = temp;
            temp = temp->next;
        }
 
        // If key was not present in linked list
        if (temp == NULL) {
            return;
        }
        
        // Unlink the node from list
        prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = temp->prev;
        }
        free(temp);  // Free memory
        L->nitems--;
        // Update Temp for next iteration of outer loop
        temp = prev->next;
        
        if (temp == NULL) {
            L->last = prev;
        }
    }
    return;
}


