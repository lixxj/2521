#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
 
static void insert_substring(char*, char*, int);
static char* substring(char*, int, int);
 
int main() {
    char *text = malloc(100*sizeof(char));strcpy(text,"<some string</h1>");
    int position;printf("%lu", strlen("#some string\n"));
    char *substring = malloc(10*sizeof(char));strcpy(substring,"h1>");

    printf("Enter the position to insert\n");
    scanf("%d", &position);

    insert_substring(text, substring, position);

    printf("%s", text);

    free(text);
    free(substring);

    return 0;
}
 
static void insert_substring(char *a, char *b, int pos) {
    char *f, *e;
    int length;
    length = strlen(a);
    if (pos < length + 1) {
        f = substring(a, 1, pos - 1);      
        e = substring(a, pos, length);
        strcpy(a, "");
        strcat(a, f);
        free(f);
        strcat(a, b);
        strcat(a, e);
        free(e);
    } 
}

static char *substring(char *string, int pos, int length) {
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
}
