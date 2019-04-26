// Written by XJ
// Xingjian, Li z5190719

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "textbuffer.h"

#define TRUE  1
#define FALSE 0

/*######################################################################
  #Blackbox tests                                                      #
  #General test ideas:                                                 #
  #For each function, create test functions to ensure the functions are#
  #working properly. Test functions should include following aspects:  #
  #1. external security holes                                          #
  #2. The flow of specific inputs through the code                     #
  #3. Expected output                                                  #
  #4. Edge situations                                                  #
  #5. Memory leaks.                     XJ                             #
  ######################################################################
*/
void CutDumptest1(void) {
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

void CutDumptest2(void) {
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

void CutDumptest3(void) {
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

void CutDumptest4(void) {
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

void DeleteDumptest1(void) {
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

void DeleteDumptest2(void) {
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

void DeleteDumptest3(void) {
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

void DeleteDumptest4(void) {
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

void PrefixDumptest1(void) {
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

void PrefixDumptest2(void) {
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

void PrefixDumptest3(void) {
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

void PrefixDumptest4(void) {
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

void MergeDumptest1(void) {
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

void MergeDumptest2(void) {
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

void MergeDumptest3(void) {
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

void PasteDumptest1(void) {
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

void PasteDumptest2(void) {
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

void PasteDumptest3(void) {
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

void SearchDumptest1(void) {
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

void SearchDumptest2() {
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

void MergeDumptestN(void) {
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

void PasteDumptestN(void) {
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

void DeleteDumptestN(void) {
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

void CutDumptestN(void) {
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

void PrefixDumptestN(void) {
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

void RichDumptest(void) {
    char str[] = "*some string*\n"
                 "_some string_\n"
                 "#some string ...\n"
                 "*some string\n"
                 "*some string*lol*\n"
                 "*some_string*again_\n"
                 "*some* _string_\n"
                 "some *string_again_\n"
                 "some#string*once_again*\n"
                 "#string_stuff_\n"
                 "*some_string_*\n"
                 "#some _string_\n"
                 "hello ** world\n"
                 "hello **world*\n"
                 "hello **world**\n";
    TB tb1 = newTB(str);
    char *s;
    
    // form Rich Text (hide line index)
    formRichText(tb1);
    s = dumpTB(tb1, FALSE);
    /*assert(strcmp(s, "<b>some string</b>\n<i>some string</i>\n<h1>some string ...</h1>\n*some string\n<b>some string</b>lol*\n<b>some_string</b>again_\n<b>some</b> <i>string</i>\nsome *string<i>again</i>\nsome#string<b>once_again</b>\n<h1>string_stuff_</h1>\n<b>some_string_</b>\n<h1>some _string_</h1>\nhello ** world\nhello *<b>world</b>\nhello *<b>world</b>*\n") == 0);*/
    assert(linesTB(tb1) == 15);
    
    free(s);
    releaseTB (tb1);
}

int main(int argc, char *argv[]) {
    
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
    RichDumptest();
    
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
    
    return EXIT_SUCCESS;
}

// The following functions are for testing Undo & Redo functions
// Since they should be commented in this assignment,
// and for my own testing and debuging,
// I didn't use assert for them but print out the output to find out
// if the output are agree with the expected output.
// And fortunately undo & redo are working eventually with the help of
// a lot of tutors and help sessions. 
// I'd like to especially thank Paul, Andrew, Micahel, Dominic and Alli
// who helped me to find out and fix some major bugs
// XJ

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

