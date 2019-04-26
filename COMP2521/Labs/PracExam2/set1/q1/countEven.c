
/* countEven.c 
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

int countEven(BSTree t){

	int isEven = 0;
    if (t == NULL) {
        return 0;
    } else if (t->key % 2 == 0) {
        isEven = 1;
    }
    
    return countEven(t->left) + countEven(t->right) + isEven;
}



