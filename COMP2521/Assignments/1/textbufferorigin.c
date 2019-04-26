// Written by XJ

// Xingjian, Li z5190719
// I'd like to especially thank Paul, Andrew, Michael, Dominic and Alli
// who helped me to find out and fix some major bugs
// XJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "textbuffer.h"

// #defines
#define TRUE  1
#define FALSE 0

// Structure of a single line, a node of doubly-linked list
typedef struct line {
      struct line *prev;        // previous line in textbuffer
      struct line *next;        // next line in textbuffer
      char *text;               // string in this line
} line;

/* A textbuffer is an ordered collection of strings
 * where each string represents one line of a text file 
 * Each line must be represented as a character array
 * Lines are connected by Doubly-linked list
 * Textbuffers are connected by Doubly-linked list
 */
typedef struct textbuffer {
      int  nitems;              // count of lines in textbuffer
      line *firstl;             // first line in textbuffer
      line *lastl;              // last line in textbuffer
      struct textbuffer *prev;  // previous textbuffer version
      struct textbuffer *next;  // next textbuffer version     
} textbuffer;

// Function prototypes (private functions)
static TB copyTB (TB tb);
static TB emptyTB(void);
static line* newline(char *it);
static void freenewTB(TB tb);
static void itoa(int num, char *linenum);
static void reverse(char str[], int length);
static void timemachine(TB tb);
static void freeoldTB(TB tb);
static void movedata(TB dest, TB src);
static void deloneTB(TB tb);
//static void insert_substring(char*, char*, int);
//static char* substring(char*, int, int);

// the following are whitebox tests prototypes (private functions)
static void CutDumptest1(void);
static void CutDumptest2(void);
static void CutDumptest3(void);
static void CutDumptest4(void);
static void DeleteDumptest1(void);
static void DeleteDumptest2(void);
static void DeleteDumptest3(void);
static void DeleteDumptest4(void);
static void MergeDumptest1(void);
static void MergeDumptest2(void);
static void MergeDumptest3(void);
static void PasteDumptest1(void);
static void PasteDumptest2(void);
static void PasteDumptest3(void);
static void PrefixDumptest1(void);
static void PrefixDumptest2(void);
static void PrefixDumptest3(void);
static void PrefixDumptest4(void);
static void SearchDumptest1(void);
static void SearchDumptest2(void);
static void MergeDumptestN(void);
static void PasteDumptestN(void);
static void DeleteDumptestN(void);
static void CutDumptestN(void);
static void PrefixDumptestN(void);
// function prototypes for undo & redo tests 
/*
static void Undoredopastetest(void);
static void Undoredomergetest(void);
static void Undoredodeletetest(void);
static void Undoredocuttest(void);
static void UndoredotestN(void);
*/

// Allocate an empty textbuffer (private function)
static TB emptyTB(void) {
    
    TB tb = malloc(sizeof(struct textbuffer));
	assert (tb != NULL);
	tb->nitems = 0;
	tb->firstl = NULL;
	tb->lastl = NULL;
	tb->prev = NULL;
	tb->next = NULL;
	
	return tb;
}

// Create a new line of given string (private function)
static line* newline(char *it) {
	
	line *new = malloc(sizeof(line));
	assert(new != NULL);
	new->text = malloc((strlen(it) + 144) * sizeof(char)); 
	if (strlen(it) == 0) {
	    new->text[0] = '\0';
	    return new;
	}
	strcpy(new->text, it);
	new->prev = new->next = NULL;
	
	return new;
}

/* Allocate a new textbuffer whose contents is initialised 
 * with the text given in the array.
 */                      
TB newTB(char text[]) {
	
	TB tb = emptyTB();
	int itext = 0;
	line *new;
	while (text[itext] != '\0') {
	    // calculate length of line and malloc
	    int len = strlen(text);
	    char *input = malloc((len + 2) * sizeof(char));
	    // copy chars before new line to "input" string
	    int iin = 0;
	    while (text[itext] != '\n') {
	        input[iin] = text[itext];
	        iin++;
	        itext++;
        }
        // lines terminated by '\n'
        input[iin] = '\n';
        input[++iin] = '\0';
        iin++;
        itext++;
        // build current line 
        new = newline(input);
        // free "input" string
        free(input);
        // connect current line to the textbuffer
        if (tb->lastl == NULL) {
	        tb->firstl = tb->lastl = new;
        } else {
	        tb->lastl->next = new;
	        new->prev = tb->lastl;
	        tb->lastl = new;
        }
        tb->nitems++;
	}	
	
	return tb;
}

// Make a copy of the CURRENT VERSION of textbuffer (private function)
static TB copyTB (TB tb) {
    
    TB copy = emptyTB();
    copy->nitems = tb->nitems;
    line *currl = tb->firstl;
    while (currl != NULL) {
        line *new = newline(currl->text);
        if (copy->lastl == NULL) {
	        copy->firstl = copy->lastl = new;
        } else {
	        copy->lastl->next = new;
	        new->prev = copy->lastl;
	        copy->lastl = new;
        }
        currl = currl->next;
    }
    
    return copy;
}

/* Free the memory occupied by the given textbuffer. 
 * It is an error to access the buffer afterwards.
 * !!! free All the versions of textbuffer.
 */
void releaseTB(TB tb) {
    
    assert(tb != NULL);
	// free "old" versions of current textbuffer
	TB backtb = tb->prev;
	while (backtb != NULL) {
	    line *curr, *prev;
	    curr = backtb->firstl;
	    while (curr != NULL) {
		    prev = curr;
		    curr = curr->next;
		    free(prev->text);
		    free(prev);
	    }
	    TB temp1 = backtb;
	    backtb = backtb->prev;
	    free(temp1);
    }
    
    // free current textbuffer and "new" versions
    while (tb != NULL) {
	    line *curr, *prev;
	    curr = tb->firstl;
	    while (curr != NULL) {
		    prev = curr;
		    curr = curr->next;
		    free(prev->text);
		    free(prev);
	    }
	    TB temp = tb;
	    tb = tb->next;
	    free(temp);
	}
}

// Free new versions of textbuffer(exclude current tb)(private function)
static void freenewTB(TB tb) {
    
    assert(tb != NULL);
	TB fronttb = tb->next;
	tb->next = NULL;
	while (fronttb != NULL) {
	    line *curr = fronttb->firstl;
	    while (curr != NULL) {
		    line *prev = curr;
		    curr = curr->next;
		    free(prev->text);
		    free(prev);
	    }
	    TB temp = fronttb;
	    fronttb = fronttb->next;
	    free(temp);
	}
}

// Free old versions of textbuffer(exclude current tb)(private function)
static void freeoldTB(TB tb) {
    
    assert(tb != NULL);
    TB backtb = tb->prev;
    tb->prev = NULL;
	while (backtb != NULL) {
	    line *curr = backtb->firstl;
	    while (curr != NULL) {
		    line *prev = curr;
		    curr = curr->next;
		    free(prev->text);
		    free(prev);
	    }
	    TB temp = backtb;
	    backtb = backtb->prev;
	    free(temp);
    }
}

// free new versions and make copy of current version
// insert copy before current version (private function)
// ensure 11- versions maximum(max 10 redo operations)
static void timemachine(TB tb) {
    
    // free new versions
	freenewTB(tb);
	// make a copy for operation and connect
	TB copy = copyTB(tb);
	
	// insert copy before current tb
	if (tb->prev == NULL) {
	    tb->prev = copy;
	    copy->next = tb;
    } else {
        tb->prev->next = copy;
        copy->prev = tb->prev;
        copy->next = tb;
        tb->prev = copy;
	}
	
	// This part ensure versions are less than 11(max 10 operations)
	// I don't why did they set this criteria of max
	// If you want unlimited undo and redo operations,
	// simply comment the following part and relevant functions
	// XJ
	
	// count amount of versions
	TB v = tb;
	int vcount = 1;
	while (v != NULL) {
	    vcount++;
	    v = v->prev;
    }
    // free too old versions
    if (vcount > 11) {
        TB w = tb;
        int wcount = 1;
        while (wcount < 11) {
            w = w->prev;
            wcount++;
        }
        freeoldTB(w);
	}
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number if showLineNumbers == TRUE
 */
char *dumpTB(TB tb, int showLineNumbers) {
	
	assert(tb != NULL);
	// calculate total length of text
	int tlen = 0;
	line *temp = tb->firstl;
	if (temp == NULL) {
	    char *y = malloc(sizeof(char));
	    y[0] = '\0';
	    return y;
	}
	while (temp != NULL) {
	    int len = strlen(temp->text);
	    tlen = tlen + len;
	    temp = temp->next;
	}
	
	// malloc string "all" for all text
	// it's caller's responsibility to free "all"      
	char *all = malloc((tlen + 13 * tb->nitems) * sizeof(char));
	if (tlen == 0) {
	    free(all);
	    return "";
	} else {
	    all[0] = 0;
    }
	line *curr = tb->firstl;
	
	if (showLineNumbers) {
	    int nline = 1;
	    while (curr != NULL) {
	        // the max integer is 2 billion(2000000000 - ten digits)
	        char *linenum = malloc(13 * sizeof(char));
	        itoa(nline, linenum);
	        strcat(all, linenum);
	        strcat(all, ". ");
	        strcat(all, curr->text);
	        free(linenum);
	        nline++;
            curr = curr->next;
	    } 
	} else {
	    while (curr != NULL) {
	        strcat(all, curr->text);
            curr = curr->next;
	    } 
	}
	
	return all;
}

// integer to Ascii (private function)
static void itoa(int num, char *linenum) { 
    
    int i = 0;  
    int base = 10;
    char str[11];
    if (num == 0) { 
        str[i++] = '0'; 
        str[i] = '\0'; 
        strcpy(linenum, str);
        return; 
    } 
    while (num != 0) { 
        int rem = num % base; 
        str[i++] = (rem > 9)? (rem - 10) + 'a' : rem + '0'; 
        num = num/base; 
    } 
    str[i] = '\0'; 
    reverse(str, i); 
    strcpy(linenum, str);
} 

// A utility function to reverse a string (private function)
static void reverse(char str[], int length) { 
    
    int start = 0; 
    int end = length - 1; 
    while (start < end) { 
        char temp = *(str+start);
        *(str+start) = *(str+end);
        *(str+end) = temp;
        start++; 
        end--; 
    } 
} 

/* Return the number of lines of the given textbuffer.
 */
int linesTB(TB tb) {
	assert(tb != NULL);
	
	return (tb->nitems);
}

/* Add a given prefix to all lines between pos1 and pos2
 * The program is to abort() with an error message if line 'pos1' or line
 * 'pos2' is out of range.  
 * The first line of a textbuffer is at position 0.
 */
void addPrefixTB(TB tb, int pos1, int pos2, char *prefix) {
    
    assert(tb != NULL);
    // abort when error occurs
    int nlines = linesTB(tb);
    if (pos1 > pos2) {
        printf("addPrefixTB ERROR: pos1 after pos2\n");
        abort();
    } else if (pos1 < 0 || pos1 >= nlines) {
        printf("addPrefixTB ERROR: pos1 exceed range\n");
        abort();
    } else if (pos2 >= nlines || pos2 < 0) {
        printf("addPrefixTB ERROR: pos2 exceed range\n");
        abort();
    }
    // add prefix
    int lcount = 0;
    line *curr = tb->firstl;
    while (lcount != pos1) {
        curr = curr->next;
        lcount++;
    }
    while (lcount >= pos1 && lcount < pos2 && curr != NULL) {
        char *p = malloc((strlen(prefix) + strlen(curr->text) + 1) * sizeof(char));
        strcpy(p, prefix);
        strcat(p, curr->text);
        strcpy(curr->text, p);
        free(p);
        curr = curr->next;
        lcount++;
    }
    char *p = malloc((strlen(prefix) + strlen(curr->text) + 1) * sizeof(char));
    strcpy(p, prefix);
    strcat(p, curr->text);
    strcpy(curr->text, p);
    free(p);
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2) {
    
    assert(tb1 != NULL);
    assert(tb2 != NULL);
    // abort when error occurs
    int nlines = linesTB(tb1);
    if (pos > nlines || pos < 0) {
        printf("mergeTB ERROR: pos out of range\n");
        abort();
    } 
    
    // prepare for undo & redo
    timemachine(tb1);
    
    // merge process
    if (tb2->nitems == 0) {
        releaseTB(tb2);
        
        return;
    }
    if (tb1->nitems == 0) {
        TB fake = copyTB(tb2);
        tb1->firstl = fake->firstl;
        tb1->lastl = fake->lastl;
        tb1->nitems = fake->nitems; 
        free(fake);
        releaseTB(tb2);
        
        return;
    }
    int lcount = 0;
    line *curr = tb1->firstl;
    while (lcount != pos - 1 && curr != NULL) {
        curr = curr->next;
        lcount++;
    }
    tb1->nitems = tb1->nitems + tb2->nitems;
    // make a copy of current version tb2
    TB fake2 = copyTB(tb2);
    // free all versions of tb2
    releaseTB(tb2);
    // connect
    if (pos == 0) {
        fake2->lastl->next = tb1->firstl;
        tb1->firstl->prev = fake2->lastl;
        tb1->firstl = fake2->firstl;
        free(fake2);
        
        return;
    } else if (nlines == pos) {
        tb1->lastl->next = fake2->firstl;
        fake2->firstl->prev = tb1->lastl;
        tb1->lastl = fake2->lastl;
        free(fake2);
        
        return;
    } else if (curr == NULL) {
        tb1->lastl->next = fake2->firstl;
        fake2->firstl->prev = tb1->lastl;
        tb1->lastl = fake2->lastl;
        free(fake2);
        
        return;
    } else {
        line *temp = curr->next;
        curr->next = fake2->firstl;
        fake2->firstl->prev = curr;
        temp->prev = fake2->lastl;
        fake2->lastl->next = temp;
        free(fake2);
        
        return;
    }
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
    assert(tb1 != NULL);
    assert(tb2 != NULL);
    // abort when error occurs
    int nlines = linesTB(tb1);
    if (pos > nlines || pos < 0) {
        printf("pasteTB ERROR: POS OUT OF RANGE\n");
        abort();
    } 
    
    // prepare for undo & redo
    timemachine(tb1);
    
    // paste process
    if (tb2->nitems == 0) {
        
        return;
    }
    if (tb1->nitems == 0) {
        TB fake = copyTB(tb2);
        tb1->firstl = fake->firstl;
        tb1->lastl = fake->lastl;
        tb1->nitems = fake->nitems; 
        free(fake);
        
        return;
    }
    int lcount = 0;
    line *curr = tb1->firstl;
    while (lcount != pos - 1 && curr != NULL) {
        curr = curr->next;
        lcount++;
    }
    tb1->nitems = tb1->nitems + tb2->nitems;
    // make a copy of current version tb2
    TB fake2 = copyTB(tb2);
    // connect
    if (pos == 0) {
        fake2->lastl->next = tb1->firstl;
        tb1->firstl->prev = fake2->lastl;
        tb1->firstl = fake2->firstl;
        free(fake2);
        
        return;
    } else if (nlines == pos) {
        tb1->lastl->next = fake2->firstl;
        fake2->firstl->prev = tb1->lastl;
        tb1->lastl = fake2->lastl;
        free(fake2);
        
        return;
    } else if (curr == NULL) {
        tb1->lastl->next = fake2->firstl;
        fake2->firstl->prev = tb1->lastl;
        tb1->lastl = fake2->lastl;
        free(fake2);
        
        return;
    } else {
        line *temp = curr->next;
        curr->next = fake2->firstl;
        fake2->firstl->prev = curr;
        temp->prev = fake2->lastl;
        fake2->lastl->next = temp;
        free(fake2);
        
        return;
    }
}

/* Cut the lines between and including 'from' and 'to' out of the 
 * textbuffer 'tb'.
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' 
 *   is outof range.
 */
TB cutTB (TB tb, int from, int to){
    
    assert(tb != NULL);
    // abort when error occurs
    int nlines = linesTB(tb);
    if (from > to) {
        printf("cutTB ERROR: from after to\n");
        abort();
    } else if (from < 0 || from >= nlines) {
        printf("cutTB ERROR: from exceed range\n");
        abort();
    } else if (to >= nlines || to < 0) {
        printf("cutTB ERROR: to exceed range\n");
        abort();
    }
    
    // prepare for undo & redo
    timemachine(tb);
    
    // cut process
    line *curr = tb->firstl;
    int lcount = 0;
    while (lcount < from) {
        lcount++;
        curr = curr->next;
    }
    line *temp1 = curr->prev;
    curr->prev = NULL;
    while (lcount < to) {
        lcount++;
        curr = curr->next;
    }
    line *temp2 = curr->next;
    curr->next = NULL;
    int flag = 0;
    if (temp1 != NULL && temp2 != NULL && flag == 0) {
        temp1->next = temp2;
        temp2->prev = temp1;
        flag = 1;
    } else if (temp1 == NULL && temp2 == NULL && flag == 0) {
        tb->firstl = tb->lastl = NULL;
        flag = 1;
    } else if (temp1 == NULL && flag == 0) {
        temp2->prev = NULL;
        tb->firstl = temp2;
        flag = 1;
    } else if (temp2 == NULL && flag == 0) {
        temp1->next = NULL;
        tb->lastl = temp1;
        flag = 1;
    } 
    tb->nitems = tb->nitems - (to - from + 1);
    // put the cut lines to new textbuffer
    TB cut = emptyTB();
    cut->lastl = curr;
    while (curr->prev != NULL) {
        cut->nitems++;
	    curr = curr->prev;
	}
	cut->firstl = curr;
	cut->nitems++;
	
	return cut;
}

/* Remove the lines between and including 'from' and 'to' from the 
 * textbuffer 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' 
 *   is out of range.
 */
void deleteTB(TB tb, int from, int to){
    
    assert(tb != NULL);
    // abort when error occurs
    int nlines = linesTB(tb);
    if (from > to) {
        printf("deleteTB ERROR: from after to\n");
        abort();
    } else if (from < 0 || from >= nlines) {
        printf("deleteTB ERROR: from exceed range\n");
        abort();
    } else if (to >= nlines || to < 0) {
        printf("deleteTB ERROR: to exceed range\n");
        abort();
    }
    
    // prepare for undo & redo
    timemachine(tb);
    
    // delete process
    line *curr = tb->firstl;
    int lcount = 0;
    while (lcount < from) {
        lcount++;
        curr = curr->next;
    }
    line *temp1 = curr->prev;
    curr->prev = NULL;
    while (lcount < to) {
        lcount++;
        curr = curr->next;
    }
    line *temp2 = curr->next;
    curr->next = NULL;
    int flag = 0;
    if (temp1 != NULL && temp2 != NULL && flag == 0) {
        temp1->next = temp2;
        temp2->prev = temp1;
        flag = 1;
    } else if (temp1 == NULL && temp2 == NULL && flag == 0) {
        tb->firstl = tb->lastl = NULL;
        flag = 1;
    } else if (temp1 == NULL && flag == 0) {
        temp2->prev = NULL;
        tb->firstl = temp2;
        flag = 1;
    } else if (temp2 == NULL && flag == 0) {
        temp1->next = NULL;
        tb->lastl = temp1;
        flag = 1;
    } 
    tb->nitems = tb->nitems - (to - from + 1);
    // free deleted lines
    line *temp;
    while (curr != NULL) {
        temp = curr;
        curr = curr->prev;
        free(temp->text);
        free(temp);
    }
}

/*  Return a linked list of Match nodes of all the matches of string 
 *  search in tb
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search) {
	
	assert(tb != NULL);
	// go through lines and search
	Match first = NULL;
	Match last = NULL;
	int lnum = 1;
	line *currl = tb->firstl;
	while (currl != NULL) {
	    int llen = strlen(currl->text);
	    char *src = malloc((llen + 1) * sizeof(char));
	    strcpy(src, currl->text);
	    char *start = src;
	    while ((src = strstr(src, search)) != NULL ) {
            int pos = src - start;
            // make new node and connect
            Match new = malloc(sizeof(matchNode));
            new->lineNumber = lnum;
            new->charIndex = pos;
            new->next = NULL;
            if (last == NULL) {
                first = last = new;
            } else {
                last->next = new;
                last = new;
            }
            src++;
        }
        // free the string of curr line and update curr line
        free(start);
	    currl = currl->next;
	    lnum++;
	}
	
	return first;
}

/* Search every line of tb for each occurrence of a set of specified 
 * subsitituions and alter them accordingly
 */
void formRichText(TB tb){
    
    assert(tb != NULL);
    /*line *currl = tb->firstl;
    while (currl != NULL) {
        // for each line
        int len = strlen(currl->text);
        // #
        if (currl->text[0] == '#') {
            currl->text[0] = '<';
            insert_substring(currl->text, "</h1>", len - 1);
            insert_substring(currl->text, "h1>", 0);
            return;
        }
        
        int i = 0;
        int flag1 = OFF;
        int flag2 = OFF;
        while (currl->text[i] != '\n') {
            
            // *
            
            
            // _
            
            
            
            i++;
        }
        // update current line
        currl = currl->next;
    }*/
}

// insert a substring to string after position
/*static void insert_substring(char *a, char *b, int pos) {
    char *f, *e;
    int length;
    length = strlen(a);
    if (pos < length) {
        f = substring(a, 1, pos + 1);      
        e = substring(a, pos, length - pos - 1);
        strcpy(a, "");
        strcat(a, f);
        free(f);
        strcat(a, b);
        strcat(a, e);
        free(e);
    } 
}*/

/*static char *substring(char *string, int pos, int length) {
    char *pointer = malloc(length + 1);
    int c;
    assert(pointer != NULL);
    for(c = 0 ; c < length ; c++) {
       if (pos == 0) {
           pos++;
       }
       *(pointer + c) = *((string + pos - 1) + c);       
    }
    *(pointer+c) = '\0';
    return pointer;
}*/

/* reverse recently called operations on tb. 
 * Applicable operations are, deleteTB, mergeTB, pasteTB and cutTB. 
 * Each time undoTB isint nlines = linesTB(tb); called, one operation is reversed on tb. 
 * When the maximum number of allowable undo operations is reached, 
 * nothing is done on tb.
 */
void undoTB (TB tb) {
    
    assert(tb != NULL);
    if (tb->prev != NULL) {
        TB copy = copyTB(tb);
        movedata(tb, tb->prev);
        deloneTB(tb->prev);
        if (tb->next == NULL) {
            tb->next = copy;
            copy->prev = tb;
        } else {
            copy->next = tb->next;
            copy->prev = tb;
            tb->next->prev = copy;
            tb->next = copy;
        }
    } 
}

/* redo one operation on tb per function call. 
 * However, when a new operation is called on tb, 
 * any reversed operations cannot be executed again with redoTB.
 */
void redoTB (TB tb) {
    
    assert(tb != NULL);
    if (tb->next != NULL) {
        TB copy = copyTB(tb);
        movedata(tb, tb->next);
        deloneTB(tb->next);
        if (tb->prev == NULL) {
            tb->prev = copy;
            copy->next = tb;
        } else {
            copy->next = tb;
            copy->prev = tb->prev;
            tb->prev->next = copy;
            tb->prev = copy;
        }
    } else {
        // printf("redoTB ERROR: NO MORE REDO OPTION\n");
    }
}

// free data of dest, move the data of src to dest (private function)
static void movedata(TB dest, TB src) {
    
    // free lines of curr tb
    line *currl = dest->firstl;
    while (currl != NULL) {
        line *temp = currl;
        currl = currl->next;
        free(temp->text);
        free(temp);
    }
    
    // move data
    dest->nitems = src->nitems;
    dest->firstl = src->firstl;
    dest->lastl = src->lastl;
    src->lastl = NULL;
    src->firstl = NULL;
}

// delete a tb, only apply to tb has no line (private function)
static void deloneTB(TB tb) {
    
    if (tb->next == NULL && tb->prev == NULL) {
        free(tb);
    } else if (tb->next == NULL) {
        tb->prev->next = NULL;
        free(tb);
    } else if (tb->prev == NULL) {
        tb->next->prev = NULL;
        free(tb);
    } else {
        tb->prev->next = tb->next;
        tb->next->prev = tb->prev;
        free(tb);
    }
}

/*######################################################################
  #Whitebox tests                                                      #
  #General test ideas:                                                 #
  #For each function, create test functions to ensure the functions are#
  #working properly. Test functions should include following aspects:  #
  #1. Internal security holes                                          #
  #2. Broken or poorly structured paths in the coding processes        #
  #3. The flow of specific inputs through the code                     #
  #4. Expected output                                                  #
  #5. The functionality of conditional loops                           #
  #And most significantly, test edge situations and memory leaks. XJ   #
  ######################################################################
*/
void whiteBoxTests(void) {
    
    // single operation all situations tests
    CutDumptest1();
    CutDumptest2();
    CutDumptest3();
    CutDumptest4();
    DeleteDumptest1();
    DeleteDumptest2();
    DeleteDumptest3();
    DeleteDumptest4();
    MergeDumptest1();
    MergeDumptest2();
    MergeDumptest3();
    PasteDumptest1();
    PasteDumptest2();
    PasteDumptest3();
    PrefixDumptest1();
    PrefixDumptest2();
    PrefixDumptest3();
    PrefixDumptest4();
    SearchDumptest1();
    SearchDumptest2();
    
    // multiple operations tests
    MergeDumptestN();
    PasteDumptestN();
    DeleteDumptestN();
    CutDumptestN();
    PrefixDumptestN();
    
    // Undo & Redo tests
    // Undoredopastetest();
    // Undoredomergetest();
    // Undoredodeletetest();
    // Undoredocuttest();
    // UndoredotestN();
    
}

// Whitebox Test Functions
static void CutDumptest1(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    
    // Cut first 2 lines of tb1 to tb2(hide line index)
    tb2 = cutTB(tb1, 0, 1);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 03\n") == 0);
    assert(linesTB(tb1) == 1);
    free(s);
    
    s = dumpTB(tb2, FALSE);
    assert(strcmp(s, "line 01\nline 02\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void CutDumptest2(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    
    // Cut last 2 lines of tb1 to tb2(show line index)
    tb2 = cutTB(tb1, 1, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n") == 0);
    assert(linesTB(tb1) == 1);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 02\n2. line 03\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void CutDumptest3(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    
    // Cut all lines of tb1 to tb2(show line index)
    tb2 = cutTB(tb1, 0, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "") == 0);
    assert(linesTB(tb1) == 0);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 03\n") == 0);
    assert(linesTB(tb2) == 3);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void CutDumptest4(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    
    // Cut line 1 to 2 in the middle of tb1 to tb2(show line index)
    tb2 = cutTB(tb1, 1, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 04\n") == 0);
    assert(linesTB(tb1) == 2);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 02\n2. line 03\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void DeleteDumptest1(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    
    // delete first 2 lines of tb1(hide line index)
    deleteTB(tb1, 0, 1);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 03\n") == 0);
    assert(linesTB(tb1) == 1);
    free(s);
    
    releaseTB (tb1);
}

static void DeleteDumptest2(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    
    // delete last 2 lines of tb1(show line index)
    deleteTB(tb1, 1, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n") == 0);
    assert(linesTB(tb1) == 1);
    free(s);
    
    releaseTB (tb1);
}

static void DeleteDumptest3(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    // delete all lines of tb1(show line index)
    deleteTB(tb1, 0, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "") == 0);
    assert(linesTB(tb1) == 0);
    free(s);
    releaseTB (tb1);
}

static void DeleteDumptest4(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n";
    TB tb1 = newTB(str);
    char *s;
    
    // delete line 1 to 2 in the middle of tb1(show line index)
    deleteTB(tb1, 1, 2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 04\n") == 0);
    assert(linesTB(tb1) == 2);
    free(s);
    
    releaseTB (tb1);
}

static void PrefixDumptest1(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    char pre[7] = "prefix";
    
    // add prefix to all lines of tb(hide line index)
    addPrefixTB(tb1, 0, 2, pre);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "prefixline 01\nprefixline 02\nprefixline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB(tb1);
}

static void PrefixDumptest2(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    char pre[7] = "prefix";
    
    // add prefix to first line of tb(hide line index)
    addPrefixTB(tb1, 0, 0, pre);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "prefixline 01\nline 02\nline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB (tb1);
}

static void PrefixDumptest3(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    char pre[7] = "prefix";
    
    // add prefix to last 2 lines in the tb(hide line index)
    addPrefixTB(tb1, 1, 2, pre);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nprefixline 02\nprefixline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB (tb1);
}

static void PrefixDumptest4(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    char pre[7] = "prefix";
    
    // add prefix to second line in the middle of tb(hide line index)
    addPrefixTB(tb1, 1, 1, pre);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nprefixline 02\nline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB (tb1);
}

static void MergeDumptest1(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    
    // merge tb2 before first line of tb1(show line index)
    mergeTB(tb1, 0, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 06\n2. line 07\n3. line 01\n4. line 02\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    releaseTB(tb1);
}

static void MergeDumptest2(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    
    // merge tb2 after first line of tb1(show line index)
    mergeTB(tb1, 1, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 06\n3. line 07\n4. line 02\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    releaseTB(tb1);
}

static void MergeDumptest3(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    
    // merge tb2 after last line of tb1(show line index)
    mergeTB(tb1, 2, tb2);
    s = dumpTB(tb1,TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 06\n4. line 07\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    releaseTB(tb1);
}

static void PasteDumptest1(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    
    // paste tb2 before first line of tb1(show line index)
    pasteTB(tb1, 0, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 06\n2. line 07\n3. line 01\n4. line 02\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 06\n2. line 07\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void PasteDumptest2(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    
    // paste tb2 after second line of tb1(show line index)
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 06\n3. line 07\n4. line 02\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 06\n2. line 07\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void PasteDumptest3(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n"
                  "line 07\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);
    char *s;
   
    // paste tb2 after last line of tb1(show line index)
    pasteTB(tb1, 2, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 06\n4. line 07\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 06\n2. line 07\n") == 0);
    assert(linesTB(tb2) == 2);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

static void SearchDumptest1(void) {
    char str[] = "line 01\n"
                 "line 02 target\n"
                 "line 03\n"
                 "line 04\n"
                 "line target 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "target line 10\n";
    TB tb1 = newTB(str);
    
    Match result = searchTB (tb1, "target");
    Match prev = result;
    assert(result->lineNumber == 2);
    assert(result->charIndex == 8);
    result = result->next;
    free(prev);
    prev = result;
    
    assert(result->lineNumber == 5);
    assert(result->charIndex == 5);
    result = result->next;
    free(prev);
    prev = result;
    
    assert(result->lineNumber == 10);
    assert(result->charIndex == 0);
    result = result->next;
    free(prev);
    prev = result;
    
    char *s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02 target\nline 03\nline 04\nline target 05\nline 06\nline 07\nline 08\nline 09\ntarget line 10\n") == 0);
    assert(linesTB(tb1) == 10);
    free(s);
    
    releaseTB (tb1);
}

static void SearchDumptest2() {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n";
    TB tb1 = newTB(str);
    Match result = searchTB (tb1, "target");
    assert(result == NULL);
    
    char *s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02\nline 03\nline 04\nline 05\nline 06\nline 07\nline 08\nline 09\nline 10\n") == 0);
    assert(linesTB(tb1) == 10);
    free(s);
    
    releaseTB (tb1);
}

static void MergeDumptestN(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);
    char *s;
    
    // merge to line 2(hide line index)
    mergeTB(tb1, 2, tb2);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02\nline 06\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    // merge to line 2(show line index)
    tb2 = newTB(str2);
    mergeTB(tb1, 2, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 06\n4. line 06\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    // merge to line 2(hide line index)
    tb2 = newTB(str2);
    mergeTB(tb1, 2, tb2);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02\nline 06\nline 06\nline 06\n") == 0);
    assert(linesTB(tb1) == 5);
    free(s);
    
    releaseTB(tb1);
}

static void PasteDumptestN(void) {
    char str1[] = "line 01\n"
                  "line 02\n";
    char str2[] = "line 06\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);
    char *s;
    
    // paste to line 2(hide line index)
    pasteTB(tb1, 2, tb2);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02\nline 06\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    // paste to line 2(show line index)
    pasteTB(tb1, 2, tb2);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 06\n4. line 06\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    // paste to line 2(hide line index)
    pasteTB(tb1, 2, tb2);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "line 01\nline 02\nline 06\nline 06\nline 06\n") == 0);
    assert(linesTB(tb1) == 5);
    free(s);
    
    releaseTB(tb1);
    releaseTB(tb2);
}

static void DeleteDumptestN(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 02\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n";
    TB tb1 = newTB(str);
    char *s;
    
    // delete line 1 to 1 in the middle of tb1(show line index)
    deleteTB(tb1, 1, 1);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 02\n4. line 03\n5. line 04\n") == 0);
    assert(linesTB(tb1) == 5);
    free(s);
    
    // delete line 1 to 1 in the middle of tb1(show line index)
    deleteTB(tb1, 1, 1);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 03\n4. line 04\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    // delete line 1 to 1 in the middle of tb1(show line index)
    deleteTB(tb1, 1, 1);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 03\n3. line 04\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB (tb1);
}

static void CutDumptestN(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    
    // Cut line1 of tb1 to tb2(show line index)
    tb2 = cutTB(tb1, 1, 1);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 02\n3. line 03\n4. line 04\n") == 0);
    assert(linesTB(tb1) == 4);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 02\n") == 0);
    assert(linesTB(tb2) == 1);
    free(s);
    releaseTB (tb2);
    
    // Cut line1 of tb1 to tb2(show line index)
    tb2 = cutTB(tb1, 1, 1);
    s = dumpTB(tb1, TRUE);
    assert(strcmp(s, "1. line 01\n2. line 03\n3. line 04\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    s = dumpTB(tb2, TRUE);
    assert(strcmp(s, "1. line 02\n") == 0);
    assert(linesTB(tb2) == 1);
    free(s);
    releaseTB (tb2);
    
    releaseTB (tb1);
}

static void PrefixDumptestN(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n";
    TB tb1 = newTB(str);
    char *s;
    char pre[7] = "prefix";
    char PRE[7] = "PREFIX";
    
    // add prefix to all lines of tb(hide line index)
    addPrefixTB(tb1, 0, 2, pre);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "prefixline 01\nprefixline 02\nprefixline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    // add PREFIX to first line of tb(hide line index)
    addPrefixTB(tb1, 0, 0, PRE);
    s = dumpTB(tb1, FALSE);
    assert(strcmp(s, "PREFIXprefixline 01\nprefixline 02\nprefixline 03\n") == 0);
    assert(linesTB(tb1) == 3);
    free(s);
    
    releaseTB(tb1);
}

// The following functions are for testing Undo & Redo functions
/*void UndoredotestN(void) {
    char str1[] = "line 01\n"
                  "line 02\n"
                  "line 03\n"
                  "line 04\n"
                  "line 05\n";
                 
    char str2[] = "line 06\n"
                  "line 07\n"
                  "line 08\n"
                  "line 09\n"
                  "line 10\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    printf("***1merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***2merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***3merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***4merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***4merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***6merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***7merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***8merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    //s = dumpTB(tb1,TRUE);
    //printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    //free(s);
    
    tb2 = newTB(str2);
    printf("***9merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    releaseTB (tb1);
}*/

/*void Undoredopastetest(void) {
    char str1[] = "line 01\n"
                  "line 02\n"
                  "line 03\n"
                  "line 04\n"
                  "line 05\n";
                 
    char str2[] = "line 06\n"
                  "line 07\n"
                  "line 08\n"
                  "line 09\n"
                  "line 10\n";
    TB tb1 = newTB(str1);                
    TB tb2 = newTB(str2);
    char *s;
    printf("***paste tb2 after last line of tb1***\n");
    pasteTB(tb1, 5, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 5, tb2)\ntb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

void Undoredomergetest(void) {
    char str1[] = "line 01\n"
                  "line 02\n"
                  "line 03\n"
                  "line 04\n"
                  "line 05\n";
                 
    char str2[] = "line 06\n"
                  "line 07\n"
                  "line 08\n"
                  "line 09\n"
                  "line 10\n";
    TB tb1 = newTB(str1);
    TB tb2 = newTB(str2);;
    char *s;
    printf("***merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    releaseTB (tb1);
}

void Undoredodeletetest(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n";
    TB tb1 = newTB(str);
    char *s;
    printf("***delete all lines of tb1***\n");
    deleteTB(tb1, 0, 9);
    s = dumpTB(tb1,FALSE);
    printf ("deleteTB(tb1, 0, 9)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    releaseTB (tb1);
}

void Undoredocuttest(void) {
    char str[] = "line 01\n"
                 "line 02\n"
                 "line 03\n"
                 "line 04\n"
                 "line 05\n"
                 "line 06\n"
                 "line 07\n"
                 "line 08\n"
                 "line 09\n"
                 "line 10\n";
    TB tb1 = newTB(str);
    TB tb2;
    char *s;
    printf("***Cut first 3 lines of tb1 to tb2***\n");
    tb2 = cutTB(tb1, 0, 2);
    s = dumpTB(tb1,TRUE);
    printf ("tb2 = cutTB(tb1, 0, 2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    // Dump tb2 without line number
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1,FALSE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    releaseTB (tb1);
    releaseTB (tb2);
}*/

