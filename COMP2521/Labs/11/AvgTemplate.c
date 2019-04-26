// Written by XJ 
// Template to calculate average number of comparisons

/* Nb = number of comparisons required for building the tree
   Nt = total number of comparisons for both building and searching
   Nk = number of searches for values in tree
   Nu = number of searches for values not in tree
   average number of comparisons: (Nb+s - Nb) / (Nk + Nu) 
*/

#include<stdio.h>

int main(int argc, char *argv[]) {
    
    // For common cases
    // if (argc != 5) {
        // printf("Usage: ./Avg Nb Nt Nk Nu\n");
        // return 1;
    // }
    
    // For size 5000 input only
    if (argc != 3) {
        printf("Usage: ./Avg Nb Nt\n");
        return 1;
    }
    
    int Nb = atoi(argv[1]);
    int Nt = atoi(argv[2]);
    
    // For common cases
    // int Nk = atoi(argv[3]);
    // int Nu = atoi(argv[4]);
    
    // For size 5000 input only
    int Nk = 5000;
    int Nu = 1666;
    
    int Avg = (Nt - Nb) / (Nk + Nu);
    printf("\nAvg is %d\n", Avg);

    return 0;
}
