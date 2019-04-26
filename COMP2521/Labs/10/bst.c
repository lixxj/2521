// bst.c ... client for BSTree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BSTree.h"

#define MAXVALS 1000

int main(int argc, char *argv[])
{
	BSTree T;
	int i, n, nvals, v[MAXVALS];

	// Build tree from values in stdin
	T = newBSTree();
	nvals = 0;
	while (nvals < MAXVALS && scanf("%d",&n) == 1) {
		v[nvals++] = n;
		T = BSTreeInsert(T,n);
	}

	// Display information about constructed tree
	printf("Tree:\n");showBSTree(T);
	printf("\n#nodes = %d,  ",BSTreeNumNodes(T));
	
	// #####Comment lines below to pass original lab tests#####
	printf("\n#even = %d,  ", countEven(T));
	
	int suc = 35; // change this line to change input
	
	int result = succ(T, suc);
	if (result != -1) {
	    printf("\nsuccessor to %d is %d, ", suc, result);
    } else {
        printf("\nno successor, ");
    }
    // #####Comment lines above to pass original lab tests#####
	
	printf("#leaves = %d\n",BSTreeNumLeaves(T));
	printf("Infix  : "); BSTreeInfix(T); printf("\n");
	printf("Prefix : "); BSTreePrefix(T); printf("\n");
	printf("Postfix: "); BSTreePostfix(T); printf("\n");
	printf("ByLevel: "); BSTreeLevelOrder(T); printf("\n");

	// Check correctness of tree

	// assume no duplicates => each value produces a node
	assert(nvals == BSTreeNumNodes(T));
	// every inserted value can be found
	for (i = 0; i < nvals; i++)
		assert(BSTreeFind(T,v[i]) != 0);
	// (hopefully) non-existent value cannot be found
	assert(BSTreeFind(T,-7654321) == 0);

	dropBSTree(T);
	return 0;
}
