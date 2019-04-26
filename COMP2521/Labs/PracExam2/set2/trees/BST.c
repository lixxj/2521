#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "BST.h"

// Tree struct you have to play with
struct tree {
  Tree right, left;
  int val;
};

// template function to find minimum value node in given BST
static Tree findMinimum(Tree root)
{
    while (root->left) {
        root = root->left;
    }
 
    return root;
}

// ##### REVIEW1 #####
static int isActuallyBST(Tree t, int lo, int hi) {
    // if tree is empty, return that it is a BST
    if (t == NULL) return 1;

    // check immediate root 
    if (t->val <= lo || t->val >= hi) return 0;

    // Check if left and right are BST 
    int leftBranch = isActuallyBST(t->left, lo, t->val);
    int rightBranch = isActuallyBST(t->right,t->val, hi);
    return (leftBranch && rightBranch);
}
// Check if the given tree is actually a BST
int isBST(Tree t) {
  int inf = 9999999; //close enough to infinity for our purposes
  return isActuallyBST(t,-inf, inf);
}

/*
 * Given a pointer to a node in the tree, return its in order successor node in the tree, that is the node in the tree whose value is the smallest value larger than the value of the given node. If no successor node exists return NULL.
 */
Tree successor(Tree t, Tree target) {
    if (t->val > target->val) {
        if (successor(t->left, target) == NULL) return t;
        return successor(t->left, target); 
    } else if (t->val < target->val) {
        return successor(t->right, target); 
    } else { // t->val == target->val
        if (t->right != NULL) {
            return findMinimum(t->right); // left-most
        } 
        return NULL;
    }
}

/* 
   You are given a Tree (t), and two pointers.
   k is a pointer to the 'kth' smallest value you should go to
    E.g. for *k == 0, it should return the smallest value
         for *k == 4, it should return the 5th smallest value
   v is a pointer to an int pointer, the function should finish by pointing to the value
    E.g. You found the kth smallest value, there should be some code which says
         *v = &(t->val)
    Initially, v is set to point to NULL
  
    You can assume the tree is a BST with at least one element and no duplicates 
    and that 0 <= k < n where n is the number of nodes in the tree
*/
void getKthSmallest(Tree t, int* k, int** v) {
    int i = 0;
    Tree res = findMinimum(t);
    while (i < *k) {
        res = successor(t, res);
        i++;
    }
    if (res != NULL) *v = &(res->val);
}

/* Find the lowest common ancestor between the noes with values v1 and v2.
   You are guaranteed that both these values exist in your BST and they are
   different
   The lowest common ancestor is defined as the first node which each of
   v1 and v2 share, as they go up the tree. I.e. the root of the whole tree is
   the highest common ancestor. For the following tree:
           
            4
          /   \
         2     7
        / \   /
       1   3 6
      /
     0 
   If v1 == 3, and v2 == 7, then their lowest common ancestor is 4
   If v1 == 3, and v2 == 0, then their lowest common ancestor is 2
*/
Tree lowestCommonAnc(Tree t, int v1, int v2) {
    if (t == NULL) {
        return t;
    } else if (t->val > v1 && t->val < v2) {
        return t;
    } else if (t->val > v2 && t->val < v1) {
        return t;
    } else if (t->val > v1 && t->val > v2) {
        return lowestCommonAnc(t->left, v1, v2);
    } else if (t->val < v1 && t->val < v2) {
        return lowestCommonAnc(t->right, v1, v2);
    }
    return t;
}





































// Check if a value is in the tree
// Should return 1 if it finds it, otherwise 0
int findValue(Tree t, int v) {
    if (t == NULL) {
        return 0;
    } else if (t->val == v) {
        return 1;
    } else if (t->val > v && t->left == NULL) {
        return 0;
    } else if (t->val < v && t->right == NULL) {
        return 0;
    } else if (t->val > v) {
        return (findValue(t->left, v));
    } else {
        return (findValue(t->right, v));
    }
}

/*

   You can ignore these methods below, unless you want examples of using the tree

*/
Tree createTree() {
  return NULL;
}

void destroyTree(Tree t) {
  if (t == NULL) return;
  destroyTree(t->right);
  destroyTree(t->left);
  free(t);
}

int  getValue(Tree t) {
  return t->val;
}

Tree find(Tree t, int v) {
  if (t->val == v) return t;
  if (t->val < v) {
    return find(t->right, v);
  } else if (t->val > v) {
    return find(t->left, v);
  } else {
    return NULL;
  }
}

Tree insert(Tree t, int v) {
  if (t == NULL) {
    t = malloc(sizeof(struct tree));
    t->val = v;
    t->right = NULL;
    t->left = NULL;
  } else {
    if (t->val < v) {
      t->right = insert(t->right, v);
    } else if (t->val > v) {
      t->left = insert(t->left, v);
    }
  }
  return t;
}

Tree randInsert(Tree t, int v) {
  if (t == NULL) {
    t = malloc(sizeof(struct tree));
    t->val = v;
    t->right = NULL;
    t->left = NULL;
  } else {
    if (rand() % 2) {
      t->right = randInsert(t->right, v);
    } else {
      t->left = randInsert(t->left, v);
    }
  }
  return t;
}

int getRootVal(Tree t) {
  assert(t != NULL);
  return t->val;
}

Tree buildTree(Tree t, int* vals, int n, Tree (*insertF)(Tree, int)) {
  int i = 0;
  for (i = 0; i < n; ++i) {
    t = insertF(t, vals[i]);
  }
  return t;
}

Tree newNode(int val) {
  Tree n = malloc(sizeof(struct tree)); 
  n->val = val;
  n->left = NULL;
  n->right = NULL;
  return n;
}

Tree buildInvalidTree(int c) {
  Tree t = newNode(10); 
  switch (c) {
    case(0) :
      t->left = newNode(5);
      break;
    case(1) :
      t->right = newNode(5);
      break;
    case(2) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      break;
    case(3) :
      t->left = newNode(5);
      t->left->right = newNode(15);
      break;
    case(4) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      break;
    case(5) :
      t->left = newNode(5);
      t->left->right = newNode(15);
      break;
    case(6) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      t->left->right->left = newNode(6);
      break;
    case(7) :
      t->left = newNode(5);
      t->left->right = newNode(7);
      t->left->right->left = newNode(6);
      t->left->right->left->right = newNode(16);
      break;
  } 
  return t;
}

