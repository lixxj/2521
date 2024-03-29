// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

#define TRUE 1
#define FALSE 0
// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	int v, w;
	Graph new = malloc(sizeof(GraphRep));
	assert(new != 0);
	new->nV = nV; new->nE = 0;
	new->edges = malloc(nV*sizeof(int *));
	assert(new->edges != 0);
	for (v = 0; v < nV; v++) {
		new->edges[v] = malloc(nV*sizeof(int));
		assert(new->edges[v] != 0);
		for (w = 0; w < nV; w++)
			new->edges[v][w] = 0;
	}
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
// This function written by XJ Li and Oliver Gorman
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path) {
	assert(g != NULL);
	
	int *visited = malloc(sizeof(int)*g->nV);
	assert(visited != NULL);
	
	memset(visited, -1, g->nV*sizeof(int));
	memset(path, -1, g->nV*sizeof(int));
	int found = FALSE; 
	
	Queue toDo = newQueue();
	QueueJoin(toDo, src);
	visited[src] = src;
	
	while (!found && !QueueIsEmpty(toDo)) {
	
	    Vertex curr = QueueLeave(toDo);
	    
        if (curr == dest) {
	        found = TRUE;
	    } else {
	        
	        int currEdge = 0;
	        
	        while (currEdge < g->nV) {
	        // for each neighbour w of curr
	            int w = g->edges[curr][currEdge];   // weight from curr to neighbour
	            
	            if (visited[currEdge] == -1 && w < max) {
	                visited[currEdge] = curr;
	                QueueJoin(toDo, currEdge);
	            }
	            
	            currEdge++;
	        }
	    }
    }
    
    // no route found
    if (visited[dest] == -1) {
        return 0;
    }
    
    // same place
    if (dest == src) {
        path[0] = src;
        return 1;
    }
    
    // count pathlength 
    int pathLength = 2;
    
    for (int i = dest; visited[i] != src; i = visited[i]) {
        pathLength++;
    }   
    
    // manage "path" array
    int pathI = pathLength - 1;
    int visI = dest;
    
    path[pathI] = dest; 
    pathI--;
    
    while (visI != src) {
        path[pathI] = visited[visI];
        visI = visited[visI];
        pathI--;
    }
    
    free(visited);
	return pathLength; // returns the number of vertices stored in the path array
}



