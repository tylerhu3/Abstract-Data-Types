//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 5
// Graph.h - Header file for Graph.c
//-----------------------------------------------------------------------------

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define UNDEF -1
#define NIL -2

/*** Constructors-Destructors ***/
typedef struct GraphObj* Graph;

Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); /* TODO Pre: 1<=u<=n=getOrder(G) */
int getDiscover(Graph G, int u); /* TODO Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u); /* TODO Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);    /* TODO Pre: length(S)==getOrder(G) */

/*** Other operations ***/
Graph transpose(Graph G); //return new Graph thats Transpose(G)
Graph copyGraph(Graph G); //return new copy of Graph G
void printGraph(FILE* out, Graph G);
#endif
