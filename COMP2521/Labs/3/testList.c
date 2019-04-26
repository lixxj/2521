// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DLList.h"

// Prototype
void testInsertAfter(void);
void checkInsertAfter(DLList myList, char* test);
void testInsertBefore(void);
void checkInsertBefore(DLList myList, char* test);
void testDelete(void);
void checkDelete(DLList myList);

int main(int argc, char *argv[])
{
	// Testing Strategy
	/* The following three functions are testing the three functions in 
	DLList.c that I wrote. For every functions(ie. InsertBefore, InsertAfter, Delete)
	consider all the edge cases and normal cases: 
	1) empty
	2) only one
	3) first one
	4) in the middle 
	5) last one 
	6) some random places                */
	
	testInsertAfter();
	testInsertBefore();
	testDelete();
	return 0;
}

void testInsertAfter(void) {
    printf("z5190719@vx3:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***ASSERTING InsertAfter FUNCTION:***\n\n");
    
    // make an empty list
	DLList myListAfter = newDLList();
	
	// Test inserting into empty list by InsertAfter
	printf("EXPECTED OUTPUT: testAfterEmpty\n");
	checkInsertAfter(myListAfter, "testAfterEmpty");
	assert(DLListLength(myListAfter) == 1);	

	// Test insert after only one(also at last)
	printf("EXPECTED OUTPUT: testAfterEmpty\ntestAfterone\n");
	checkInsertAfter(myListAfter, "testAfterone");
	assert(DLListLength(myListAfter) == 2);	
	
	// Test insert after at first(also in the middle)
	DLListMove(myListAfter, -1);
	printf("EXPECTED OUTPUT: testAfterEmpty\ntestAfterfirstmiddle\ntestAfterone\n");
	checkInsertAfter(myListAfter, "testAfterfirstmiddle");
	assert(DLListLength(myListAfter) == 3);	
	
	printf("z5190719@vx3:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***InsertAfter ASSERTED SUCCESSFULLY***\n\n");
}	

void checkInsertAfter(DLList myList, char* test) {
	assert(myList != NULL);
	// show the state of the list before the operation (including curr and nitems)
	printf("BEFORE OPERATION: ");
	putDLList(stdout, myList);                              
	printf("nitems IS %d\n", DLListLength(myList));
	if (DLListLength(myList) != 0) {
	    printf("CURR IS %s\n", DLListCurrent(myList));
	} else {
	    printf("CURR IS NULL\n");
	}
	DLListAfter(myList, test);
	assert(strcmp(DLListCurrent(myList), test) == 0);
	// display the state of the list after the operation
	printf("AFTER OPERATION: ");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\n");
}

void testInsertBefore(void) {
    printf("z5190719@vx3:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***ASSERTING InsertBefore FUNCTION:***\n\n");
    
    // make an empty list
	DLList myListBefore = newDLList();
	
	// Test inserting into empty list by InsertBefore
	printf("EXPECTED OUTPUT: testBeforeEmpty\n");
	checkInsertBefore(myListBefore, "testBeforeEmpty");
	assert(DLListLength(myListBefore) == 1);	

	// Test insert before only one(also at first)
	printf("EXPECTED OUTPUT: testBeforeone\ntestBeforeEmpty\n");
	checkInsertBefore(myListBefore, "testBeforeone");
	assert(DLListLength(myListBefore) == 2);	
	
	// Test insert before at last(also in the middle)
	DLListMove(myListBefore, 1);
	printf("EXPECTED OUTPUT: testBeforeone\ntestBeforelastmiddle\ntestBeforeEmpty\n");
	checkInsertBefore(myListBefore, "testBeforelastmiddle");
	assert(DLListLength(myListBefore) == 3);	
	
	printf("z5190719@sitar:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***InsertBefore ASSERTED SUCCESSFULLY***\n\n");
}	

void checkInsertBefore(DLList myList, char* test) {
	assert(myList != NULL);
	// show the state of the list before the operation (including curr and nitems)
	printf("BEFORE OPERATION: ");
	putDLList(stdout, myList);
	printf("nitems IS %d\n", DLListLength(myList));
	if (DLListLength(myList) != 0) {
	    printf("CURR IS %s\n", DLListCurrent(myList));
	} else {
	    printf("CURR IS NULL\n");
	}
	DLListBefore(myList, test);
	assert(strcmp(DLListCurrent(myList), test) == 0);
	// display the state of the list after the operation
	printf("AFTER OPERATION: ");
	putDLList(stdout, myList);
	assert(validDLList(myList));    
	printf("\n");
}

void testDelete(void) {
    printf("z5190719@vx3:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***ASSERTING Delete FUNCTION:***\n\n");
    // make the list
	DLList myListDelete1 = newDLList();
	DLList myListDelete2 = newDLList();
	DLListBefore(myListDelete1, "testDeleteonlyA");
	DLListBefore(myListDelete1, "testDeletefirst");
	DLListAfter(myListDelete2, "testDeleteonlyB");
	DLListAfter(myListDelete2, "testDeletemiddle");
    DLListAfter(myListDelete2, "testDeletelast");
    // Test delete in the middle
    DLListMove(myListDelete2, -1);
    printf("EXPECTED OUTPUT: testDeleteonlyB\ntestDeletelast\n");
    checkDelete(myListDelete2);
    // test delete the first
    printf("EXPECTED OUTPUT: testDeleteonlyA\n");
    checkDelete(myListDelete1);
    // test delete the last
    printf("EXPECTED OUTPUT: testDeleteonlyB\n");
    checkDelete(myListDelete2);
    // check delete the only one
    printf("EXPECTED OUTPUT:\n");
    checkDelete(myListDelete1);
    printf("\nEXPECTED OUTPUT:\n");
    checkDelete(myListDelete2);
    // check delete empty list
    printf("\nEXPECTED OUTPUT:\n");
    checkDelete(myListDelete1);
    printf("z5190719@vx3:/tmp_amd/reed/export/reed/4/z5190719/COMP2521/Labs/3$\n***Delete ASSERTED SUCCESSFULLY***\n");
}

void checkDelete(DLList myList) {
	// show the state of the list before the operation (including curr and nitems)
	printf("BEFORE OPERATION: ");
	putDLList(stdout, myList);
	printf("nitems IS %d\n", DLListLength(myList));
	if (DLListLength(myList) != 0) {
	    printf("CURR IS %s\n", DLListCurrent(myList));
	} else {
	    printf("CURR IS NULL\n");
	}
	DLListDelete(myList);
	// display the state of the list after the operation
	printf("AFTER OPERATION: ");
	putDLList(stdout, myList);
	assert(validDLList(myList));
	printf("\n");
}

