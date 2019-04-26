// Written by XJ
// Xingjian, Li z5190719

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "textbuffer.h"

#define TRUE  1
#define FALSE 0

// Blackbox Tests
void CutDumptest1(void) {
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
    s = dumpTB(tb1,FALSE);
    printf ("tb2 = cutTB(tb1, 0, 2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    // Dump tb2 without line number
    s = dumpTB(tb2,FALSE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
}

void CutDumptest2(void) {
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
    printf("***Cut last 3 lines of tb1 to tb2***\n");
    tb2 = cutTB(tb1, 7, 9);
    s = dumpTB(tb1,TRUE);
    printf ("tb2 = cutTB(tb1, 7, 9)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    // Dump tb2 with line number 
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
}

void CutDumptest3(void) {
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
    printf("***Cut all lines of tb1 to tb2***\n");
    tb2 = cutTB(tb1, 0, 9);
    s = dumpTB(tb1,TRUE);
    printf ("tb2 = cutTB(tb1, 0, 9)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    // Dump tb2 with line number
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
}

void CutDumptest4(void) {
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
    // make sure input is correct after newTB
    // s = dumpTB(tb1,TRUE);printf ("tb1 = \n%s\n", s);
    printf("***Cut line 2 to 4 in the middle of tb1 to tb2***\n");
    tb2 = cutTB(tb1, 2, 4);
    s = dumpTB(tb1,TRUE);
    printf ("tb2 = cutTB(tb1, 2, 4)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    // Dump tb2 with line number
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
}

void DeleteDumptest1(void) {
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
    printf("***delete first 3 lines of tb1***\n");
    deleteTB(tb1, 0, 2);
    s = dumpTB(tb1,FALSE);
    printf ("deleteTB(tb1, 0, 2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void DeleteDumptest2(void) {
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
    printf("***delete last 3 lines of tb1***\n");
    deleteTB(tb1, 7, 9);
    s = dumpTB(tb1,FALSE);
    printf ("deleteTB(tb1, 7, 9)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void DeleteDumptest3(void) {
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
    releaseTB (tb1);
}

void DeleteDumptest4(void) {
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
    printf("***delete line 2 to 4 in the middle of tb1***\n");
    deleteTB(tb1, 2, 4);
    s = dumpTB(tb1,FALSE);
    printf ("deleteTB(tb1, 2, 4)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void PrefixDumptest1(void) {
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
    char pre[7] = "prefix";
    printf("***add prefix to all lines of tb***\n");
    addPrefixTB(tb1, 0, 9, pre);
    s = dumpTB(tb1,TRUE);
    printf ("addPrefixTB(tb1, 0, 9, prefix);\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB(tb1);
}

void PrefixDumptest2(void) {
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
    char pre[7] = "prefix";
    printf("***add prefix to first line of tb***\n");
    addPrefixTB(tb1, 0, 0, pre);
    s = dumpTB(tb1,FALSE);
    printf ("addPrefixTB(tb1, 0, 0, prefix);\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void PrefixDumptest3(void) {
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
    char pre[7] = "prefix";
    printf("***add prefix to line 4 to 6 in the middle of tb***\n");
    addPrefixTB(tb1, 4, 6, pre);
    s = dumpTB(tb1,FALSE);
    printf ("addPrefixTB(tb1, 4, 6, prefix);\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void PrefixDumptest4(void) {
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
    char pre[7] = "prefix";
    printf("***add prefix to last 3 lines of tb***\n");
    addPrefixTB(tb1, 7, 9, pre);
    s = dumpTB(tb1,FALSE);
    printf ("addPrefixTB(tb1, 7, 9, prefix);\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB (tb1);
}

void MergeDumptest1(void) {
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
    printf("***merge tb2 before first line of tb1***\n");
    mergeTB(tb1, 0, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 0, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB(tb1);
}

void MergeDumptest2(void) {
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
    TB tb2 = newTB(str2); //  FIXME
    char *s;
    printf("***merge tb2 after second line of tb1***\n");
    mergeTB(tb1, 1, tb2); // FIXME
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB(tb1);
    //releaseTB(tb2);
}

void MergeDumptest3(void) {
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
    releaseTB(tb1);
    //releaseTB(tb2);
}

void MergeDumptest4(void) {
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
    printf("***merge tb2 after last line of tb1***\n");
    mergeTB(tb1, 5, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 5, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    releaseTB(tb1);
    //releaseTB(tb2);
}

void PasteDumptest1(void) {
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
    printf("***paste tb2 before first line of tb1***\n");
    pasteTB(tb1, 0, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 0, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);
    releaseTB (tb1);
    releaseTB (tb2);
}

void PasteDumptest2(void) {
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
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
}

void PasteDumptest3(void) {
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
    printf("***paste tb2 after second last line of tb1***\n");
    pasteTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);

    releaseTB (tb1);
    releaseTB (tb2);
}

void PasteDumptest4(void) {
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
    printf("***paste tb2 after last line of tb1***\n");
    pasteTB(tb1, 5, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 5, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);
    releaseTB (tb1);
    releaseTB (tb2);
}

void Undoredopastetest(void) {
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
    s = dumpTB(tb1, TRUE);
    printf ("pasteTB(tb1, 5, tb2)\ntb1 = \n%s\n", s);
    free(s);
    //releaseTB (tb1);
    //releaseTB (tb2);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    releaseTB(tb1);
    releaseTB(tb2);
    return;
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, FALSE);
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
}

void SearchDumptest(void) {
    char str[] = "line 01\n"
                 "line 02 target\n"
                 "line 03\n"
                 "line 04\n"
                 "line target 05\n"
                 "line 06\n"
                 "line 07\n"
                 "target line 08\n"
                 "line 09\n"
                 "line 10\n";
    printf("***SearchDumptest: target positions:\nline :2 char: 8\nline :5 char: 5\nline :8 char: 0\n***\n");
    TB tb1 = newTB(str);
    Match result = searchTB (tb1, "target");
    Match pre;
    while (result != NULL) {
        printf("line: %d\nchar: %d\n", result->lineNumber, result->charIndex);
        pre = result;
        result = result->next;
        free(pre);
    }
    releaseTB (tb1);
}

void UndoredotestN(void) {
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
    
    tb2 = newTB(str2);
    printf("***2merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***3merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***4merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***4merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***6merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***7merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***8merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***9merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***10merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***11merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***12merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    tb2 = newTB(str2);
    printf("***13merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    
    s = dumpTB(tb1, TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***undoing tb1***\n");
    undoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    printf ("***redoing tb1***\n");
    redoTB(tb1);
    s = dumpTB(tb1, TRUE);
    printf ("tb1 = \n%s\n", s);
    free(s);
    
    releaseTB (tb1);
}

void MergetestN(void) {
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
    
    printf("***merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    tb2 = newTB(str2);
    printf("***merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    tb2 = newTB(str2);
    printf("***merge tb2 after second last line of tb1***\n");
    mergeTB(tb1, 4, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("mergeTB(tb1, 4, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    releaseTB (tb1);
}

void PasteDumptestN(void) {
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
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    s = dumpTB(tb2,TRUE);
    printf ("no. of lines in tb2 = %d\ntb2 = \n%s\n", linesTB(tb2), s);
    free(s);
    
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    printf("***paste tb2 after second line of tb1***\n");
    pasteTB(tb1, 1, tb2);
    s = dumpTB(tb1,TRUE);
    printf ("pasteTB(tb1, 1, tb2)\nno. of lines in tb1 = %d\ntb1 = \n%s\n", linesTB(tb1), s);
    free(s);
    
    releaseTB (tb1);
    releaseTB (tb2);
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
    printf("@@@@@EXPECT@@@@@\n<b>some string</b>\n<i>some string</i>\n<h1>some string ...</h1>\n*some string\n<b>some string</b>lol*\n<b>some_string</b>again_\n<b>some</b> <i>string</i>\nsome *string<i>again</i>\nsome#string<b>once_again</b>\n<h1>string_stuff_</h1>\n<b>some_string_</b>\n<h1>some _string_</h1>\nhello ** world\nhello *<b>world</b>\nhello *<b>world</b>*\n");
    printf("@@@@@OUTPUT@@@@@\n%s", s);
    
    free(s);
    releaseTB (tb1);
}

void RichDumptest1(void) {
    char str[] = "#some string\n";
    TB tb1 = newTB(str);
    char *s;
    
    // form Rich Text (hide line index)
    formRichText(tb1);
    s = dumpTB(tb1, FALSE);
    printf("@@@@@OUTPUT@@@@@\n%s", s);
    
    free(s);
    releaseTB (tb1);
}

int main(int argc, char *argv[]) {
    /*CutDumptest1();
    CutDumptest2();
    CutDumptest3();
    CutDumptest4();
    DeleteDumptest1();
    DeleteDumptest2();
    DeleteDumptest3();
    DeleteDumptest4();
    PasteDumptest1();
    PasteDumptest2();
    PasteDumptest3();
    PasteDumptest4();
    PrefixDumptest1();
    PrefixDumptest2();
    PrefixDumptest3();
    PrefixDumptest4();
    SearchDumptest();
    MergeDumptest1();
    MergeDumptest2();
    MergeDumptest3();
    MergeDumptest4();
    
    MergetestN();
    PasteDumptestN();
    
    Undoredopastetest();
    Undoredomergetest();
    Undoredodeletetest();
    Undoredocuttest();
    UndoredotestN();*/
    
    RichDumptest();
    //RichDumptest1();
    
    return EXIT_SUCCESS;
}


