// unsort.c ... make a sequence of numbers not sorted
// Usage: unsort [FileName]
// If no file name supplied, unsorts stdin

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main (int argc, char *argv[])
{
    FILE *in;

    if (argc == 1) 
      in = stdin;
    else {
       if ((in = fopen(argv[1],"r")) == NULL) {
          fprintf(stderr, "Can't open file '%s'\n",argv[1]);
          exit(1);
       }
    }
  
    // read numbers
    int val;
    int *arr;
    int i = 0;
    while (fscanf(in, "%d", &val) != EOF) {
        arr[i] = val;
        i++;
    }
    
    unsort(arr, i);
    
    return 0;
}      

// "unsort" them
void unsort(int *arr, int size) {
    int temp;












}
