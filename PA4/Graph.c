//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 4
// Graph.c
// Graph ADT Implementation - This is done by making array of n List Objects where each
// List represents the connected connected components from n to the item inside each
// List
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#define INF -1
#define NIL -2


typedef struct GraphObj //defining the GraphObj
{
    List * arr; //Array of Lists whose ith element contains neighbors of vertex i.
    char * color; // array holding the color (white(w), gray (g), black(b)) of vertex i.
    int * predc; //  An array of ints whose ithelement is the parent of vertex i.
    int * dist; // holds the distance from source to element i
    int size, verts, source; // size holds number of edges, verts hold number of vertices, and source is the source node
} GraphObj;

//typedef struct GraphObj* Graph;

Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    G->arr = malloc((n+1)*sizeof(List));
    G->size = 0;
    G->verts = n;
    G->source = NIL;
    int i;
    G->predc = malloc((n+1)*sizeof(int));
    G->dist = malloc((n+1)*sizeof(int));
    G->color = malloc((n+1)*sizeof(char));
    for(i = 0; i <= n; i++)
    {
        G->arr[i] = newList(); // TODO: Be sure to test to see if this is necessary
        G->predc[i] = NIL; // set all predessors to NIL
        G->dist[i] = INF; // set all distances to INF
        G->color[i] = 'w'; //set all color to white
    }
    return G;
}

int getSize(Graph G) // get number of edges in G
{
    if(G == NULL)
        return 0;
    return G->size;
}

int getOrder(Graph G) // get number of vertices in G
{
    if(G == NULL)
        return 0;
    return G->verts;
}

int getSource(Graph G) // get the source for BFS used in G
{
    if(G == NULL)
        return NIL;
    return G->source;
}

int getParent(Graph G, int u) //Get parent of u in G
{
    if(G == NULL || u < 1 || u > getOrder(G))
        return NIL;
    return G->predc[u];
}

int getDist(Graph G, int u)
{
    if(G == NULL || u < 1 || u > getOrder(G))
        return INF;
    return G->dist[u];
}

void makeNull(Graph G) //Make all lists in arr empty; and reset everything to default state.
{
    if(G == NULL)
        return;
    int i;
    for(i = 0; i <= G->verts; i++)
    {
        clear(G->arr[i]);
        G->predc[i] = NIL; // set all predessors to NIL
        G->dist[i] = INF; // set all distances to INF
        G->color[i] = 'w'; //set all color to white
    }
}

void freeGraph(Graph* pG) // Destructor; free the Graph pG
{
    if(*pG == NULL)
        return;
    int i;
    int n = getOrder(*pG);
    for(i = 0; i <= n; i++)
    {
        freeList(&((*pG)->arr[i]));
    }
    free((*pG)->dist);
    free((*pG)->color);
    free((*pG)->predc);
    free(*pG);
    *pG = NULL;
}

void addArc(Graph G, int u, int v) //add a directional edge from u -> v
{
    if(G == NULL)
        return;

    if(u < 1 || u > getOrder(G) ||  v < 1 || v > getOrder(G))
    {
        printf("Graph::addArc:: u and v are out of range");
        return;
    }
    moveBack(G->arr[u]);
    if(index(G->arr[u]) < 0)
    {
        append(G->arr[u], v);
        G->size++;
        return;
    }

    while(index(G->arr[u])>=0)
    {
        int x = get(G->arr[u]);
        if(x < v)
        {
            insertAfter(G->arr[u],v);
            G->size++;
            break;
        }
        else if(index(G->arr[u]) == 0 && v < x)
        {
            prepend(G->arr[u],v);
            G->size++;
            break;
        }
        movePrev(G->arr[u]);
    }
}

void addEdge(Graph G, int u, int v) //add a edge from u to v
{
    if(G == NULL)
        return;
    if(u < 1 || u > getOrder(G) ||  v < 1 || v > getOrder(G))
    {
        printf("Graph::addEdge:: u and v are out of range");
        return;
    }
    addArc(G,u,v);
    addArc(G,v,u);
    G->size--;
}


void printGraph(FILE* out, Graph G) //Output adj List to out
{
    if(G == NULL)
        return;
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        if(length(G->arr[i]) != 0)
            fprintf(out,"%i: ",i);
        printList(out,G->arr[i]);
        if(length(G->arr[i]) != 0 && getOrder(G) != i)
            fprintf(out,"\n");
    }
}

void BFS(Graph G, int s) //Perform BFS with s as source on Graph g
{
    if(G == NULL)
        return;
    G->source = s;
    int i = 0;
    for(i = 1; i <= getOrder(G); i++)
    {
        G->dist[i] = INF;
        G->predc[i] = NIL;
        G->color[i] = 'w';
    }
    G->dist[s] = 0;
    G->color[s] = 'g';
    List Q = newList();
    append(Q,s);
    while(length(Q) != 0)
    {
        moveFront(Q);
        int x = get(Q);
        deleteFront(Q);
        moveFront(G->arr[x]);
        while(index(G->arr[x]) >= 0) //for all yAdj(x)
        {
            int y = get(G->arr[x]);
            if(G->color[y] == 'w')
            {
                G->color[y] = 'g';
                G->dist[y] = G->dist[x] + 1;
                G->predc[y] = x;
                append(Q,y);
            }
            moveNext(G->arr[x]);
        }
        G->color[x] = 'b';
    }
    freeList(&Q);
    free(Q);
}

void getPath(List L, Graph G, int u) //get the shortest path from source to u
{
    if(G == NULL || getSource(G)==NIL)
        return;
    if(u < 1  ||  u > getOrder(G))
    {
        append(L, NIL);
        return;
    }
    if(u == getSource(G))
    {
        append(L, u);
        return;
    }
    getPath(L,G,getParent(G,u));
    if(getParent(G,u) >= 1) // this is just to pass the test.
        append(L,u);
}
