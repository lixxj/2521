# COMP2521 18s1; Question: hasPath

CC=gcc
CFLAGS=-Wall -Werror -lm -g

all: testHasPath

testHasPath :  Graph.o hasPath.o testHasPath.o
	$(CC) -o testHasPath  Graph.o  hasPath.o testHasPath.o

hasPath.o: hasPath.c Graph.h

testHasPath.o : testHasPath.c Graph.h 


clean:
	rm -f testHasPath hasPath.o testHasPath.o core



