/*
 * Question 1
 * By Matthew Di Meglio 31/05/2018
 * cs2521 2018 semester 2
 * 
 * splitAtNode(l, n) should, if n is a node in the list l,
 * split the list just before the node n
 *
 * EXAMPLE 1. If
 * l -> [1] -> [1] -> [1] -> X
 *              ^
 * n -----------+
 * Then after calling splitAtNode(l, n), should have
 * l -> [1] -> X    [1] -> [1] -> X
 *                   ^
 * n ----------------+
 *
 * EXAMPLE 2. If
 * l -> [1] -> [2] -> [3] -> X
 *       ^
 * n ----+
 * Then after calling splitAtNode(l, n), should have
 * l -> X    [1] -> [2] -> [3] -> X
 *            ^
 * n ---------+
 *
 * EXAMPLE 3. If
 * l -> [1] -> [1] -> [1] -> X
 *       
 * n -> [1] -> [1] -> X
 * Then after calling splitAtNode(l, n), should have
 * l -> [1] -> [1] -> [1] -> X
 *       
 * n -> [1] -> [1] -> X
 */

// Written by XJ Li

#include "q1.h"
int check(List l, Link n);

void splitAtNode(List l, Link n) {
    assert(l != NULL);
    // do nothing if n is not in l
    if ((n == NULL) || (check(l, n) == 0)) {
        return;
    }
    // n is l->head;
    if (n == l->head) {
        l->head = NULL;
        return;
    }
    // if n is in l and is not l->head, item >= 2
    Link last = l->head;
    Link curr = last->next;
    while (curr != NULL) {
        if (curr == n) {
            last->next = NULL;
            return;
        }
        last = last->next;
        curr = curr->next;
    }
}

// return 1 if n in l
// return 0 if n not in l
int check(List l, Link n) {
    Link curr = l->head;
    int inlist = 0;
    while (curr != NULL) {
        if (curr == n) {
            inlist = 1;
        }
        curr = curr->next;
    }

    return inlist;
}



