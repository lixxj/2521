#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "List.h"

static int dfsCycleCheck(Graph g, int v, int previous);
int visited[999];
void dfs(Graph g, int v, int group, int *res);

// graph representation (adjacency matrix)
typedef struct GraphRep {
   int   nV;    // #vertices
   int   nE;    // #edges
   int **edges; // matrix of booleans
} GraphRep;

// Write a function which takes in a Graph g and returns a 
// vertex-indexed connected components array
// e.g. a graph with the following adjacency matrix representation 
// 0 1 0 0
// 1 0 0 0
// 0 0 0 1
// 0 0 1 0
// would return the following array:
// [0, 0, 1, 1]
// i.e. vertices 0 and 1 are in the first connected component (represented by 0 in the array), and
// vertices 2 and 3 are in the second connected component (represented by 1)

// Iteration
int *components(Graph g) {
    Stack s = newStack();
    int* res = calloc(g->nV, sizeof(int));
    int i;for (i=0; i<g->nV; i++) res[i] = -1;
    
    int cpns=0;i=0;int v;
    while (i<g->nV) {
        if(res[i]==-1) pushOnto(s,i);
        while(!emptyStack(s)){
            v=popFrom(s);
            int j=0;while(j<g->nV){
                if(adjacent(g,v,j)&&res[j]==-1){
                    res[j] = cpns;
                    pushOnto(s,j);
                }
                j++;
            }
        }        
        i++;cpns++;
    }
    
    return res;
}

// Recursion
int *components(Graph g) {
    int* res = calloc(g->nV, sizeof(int));
    int i;
    for (i=0; i<g->nV; i++) res[i] = -1;
    int group = 0;
    
    for (i=0; i<g->nV; i++) {
        if (res[i] == -1) {
            dfs(g, i, group, res);
            group++;
        }
    }
    
    return res;
}

void dfs(Graph g, int v, int group, int *res) {
    res[v] = group;
    int i;
    for (i=0; i<g->nV; i++) {
        if (adjacent(g, v, i) && res[i] == -1) {   
            dfs(g, i, group, res);
        }
    }
}

/*
 * Given a unweighted/undirected graph, a starting vertex and a distance, return an array which contains all the vertices that are at most that distance away. 
 * The vertices in the array should be in order of increasing distance, and for vertices that are the same distance away, ordered from smallest to largest. 
 * You should also include the initial vertex in the array and also store the number of vertices in the array you returned in size*.
 *
 *  0 -> 1 -> 2
 *  |
 *  v
 *  3
 *  within(g,0,1,&n) ==> [0, 3, 1], n == 3
 */
int* within(Graph g, int s, int d, int *size) {
    Queue q = newQueue();
    int* dist = calloc(g->nV, sizeof(int));
    int* res = calloc(g->nV, sizeof(int));
    int i;
    for (i=0; i<g->nV; i++) dist[i] = -1;
    int ct = 0;
    int currDist = 0;
    enterQueue(q, s);
    dist[s] = currDist; 
    int v;
    res[ct++] = s;
    // BFS approach
    while (!emptyQueue(q)) {
      v = leaveQueue(q); 
      currDist = dist[v];
      // distance control
      if (currDist < d) {
          // Add all neighbours with distance currDist+1 to result&queue
          for (i= g->nV-1; i>=0; i--) {
              if (dist[i] == -1 && g->edges[v][i]==1) {
                  dist[i] = currDist+1;
                  enterQueue(q,i);
                  res[ct++] = i;
              }
          }
      }
    } 
    *size = ct;
    return res;
} 

/*
 * Cycle detection.
 *
 * Write a function which takes in an undirected Graph g, and returns 1 if
 * the graph has a cycle, 0 otherwise
 */
 // Can be solved use Stack or Queue or Recursion, XJ

// Stack->DFS
/*int hasCycle(Graph g) {
    Stack s = newStack();
    int *visited = calloc(g->nV, sizeof(int));
    int i=0;while(i<g->nV){visited[i]=-1;i++;}
    
    int v;i=0;while (i<g->nV){
        if (visited[i] == -1) {
            pushOnto(s, i);
            visited[i]=i;
            while(!emptyStack(s)){
                v = popFrom(s);
                int j=0;while(j<g->nV){
                    if(adjacent(g, v, j)){
                        if(visited[j]!=-1&&visited[v]!=j){return 1;}
                        else if(visited[j]==-1){visited[j]=v;pushOnto(s, j);}
                    }
                    j++;
                }
            }
        }
        i++;
    }
    
    // no cycle
    return 0;    
}*/

/*// Queue->BFS
int hasCycle(Graph g) {
    Queue s = newQueue();
    int* pred = calloc(g->nV,sizeof(int));
    int i;for (i=0; i<g->nV; i++) pred[i] = -1;

    for (i=0; i<g->nV; i++) {
        if (pred[i] != -1) continue;
        enterQueue(s,i);
        pred[i] = i;
        while (!emptyQueue(s)) {
            int v = leaveQueue(s);
            int j;for (j=0; j<g->nV; j++) {
                if (g->edges[v][j] == 0) continue;
                if (pred[j] != -1 && pred[v] != j) return 1; //Return 1, if we have seen the neighbour before 
                if (pred[j] != -1) continue;
                pred[j] = v; //Keep track of where we came from so we can ignore the vertex later
                enterQueue(s,j);
            }
        }    
    }
    return 0;
}*/

// Recursion
int hasCycle(Graph g) {
    if (g->nV == 0 || g->nE == 0) return 0;
    int result = 0;
    int i = 0;
    while (i < g->nV) {
        // mark all as unvisited
        int i1 = 0;
        while (i1 < g->nV) {
            visited[i1] = -1;
            i1++;
        }
        if (dfsCycleCheck(g, i, i)) result = 1;
        i++;
    }
    return result;
}

static int dfsCycleCheck(Graph g, int v, int previous) {
    visited[v] = 1; // mark as visited
    int newprevious = v;
    int curr;
    for (curr = 0; curr < g->nV; curr++) {
        if (adjacent(g, v, curr) && curr != previous) {
            if (visited[curr] != -1) {
                return 1;
            }
            else if (dfsCycleCheck(g, curr, newprevious)) {
                return 1;
            }
        }
    }
    return 0; // no cycle
}

/*
 * =============================================
 * END OF QUESTIONS 
 * ============================================
 */
int bipartition(Graph g, List l1, List l2) {
   

  return 1;
}

/*
   You can ignore these methods below, unless you want examples of using the  graph 
   */

// check validity of Vertex 
int validV(Graph g, int v)
{
  return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, int v, int w)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  Edge new = {v,w}; // struct assignment
  return new;
}

// insert a bidirectional edge from v to w
// - sets (v,w) and (w,v)
void insertBEdge(Graph g, int v, int w, int wt)
{
  insertEdge(g,v,w,wt);
  insertEdge(g,w,v,wt);
}

//insert an edge from v to w
// - sets (v,w)
void insertEdge(Graph g, int v, int w, int wt)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  if (g->edges[v][w] == 0) {
    g->edges[v][w] = wt;
    g->nE++;
  }
}
// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, int v, int w)
{
  assert(g != NULL && validV(g,v) && validV(g,w));
  if (g->edges[v][w] != 0) {
    g->edges[v][w] = 0;
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
  int v;
  for (v = 0; v < g->nV; v++) {
    free(g->edges[v]);
  }
  free(g->edges);
  free(g);

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

int adjacent(Graph g, int v, int u) {
  return !!g->edges[v][u] || !!g->edges[u][v];
}
