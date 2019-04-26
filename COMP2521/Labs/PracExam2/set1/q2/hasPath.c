#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"

static int dfs(Graph g, Vertex src, Vertex dest, int *visited);

int hasPath(Graph g, Vertex src, Vertex dest) {   
    if (src == dest) return 1;
    
    // initialise to 0 (unvisited)
    int *visited = calloc(g->nV+1, sizeof(int));
    
    return dfs(g, src, dest, visited);
}

static int dfs(Graph g, Vertex src, Vertex dest, int *visited) {
    visited[src] = 1; // mark as visited
    int i;
    for(i=0; i<g->nV; i++) {
        // all the adjacent 
        if (adjacent(g, src, i)) {
            if (i==dest) return 1;
            if (visited[i]==0 && dfs(g, i, dest, visited) == 1) return 1; 
        }
    }
    return 0;
}

/*
hasPath(G,src,dest):
|  Input  graph G, vertices src,dest
|  Output true if there is a path from src to dest in G,
|         false otherwise
|
|  return dfsPathCheck(G,src,dest)

dfs(G,v,dest):
|  mark v as visited
|  for all (v,w) of edges(G) do
|  |  if w=dest then       // found edge to dest
|  |     return true
|  |  else if w has not been visited then
|  |     if dfs(G,w,dest) then
|  |        return true    // found path via w to dest
|  |     end if
|  |  end if
|  end for
|  return false            // no path from v to dest
*/




