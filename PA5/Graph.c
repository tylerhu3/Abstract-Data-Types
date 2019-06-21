//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 5
// Graph.c
// Graph ADT Implementation - This is done by making array of n List Objects where each
// List represents the connected connected components from n to the item inside each
// List
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "List.h"
#define UNDEF -1
#define NIL -2


typedef struct GraphObj //defining the GraphObj
{
    List * arr; //Array of Lists whose ith element contains neighbors of vertex i.
    char * color; // array holding the color (white(w), gray (g), black(b)) of vertex i.
    int * parent; //  An array of ints whose ith element is the parent of vertex i.
    int * discover; // used to hold the discover time
    int * finish; // used to hold finish time
    int size, verts; // size holds number of edges, verts hold number of vertices, and source is the source node
    int time;
} GraphObj;

Graph newGraph(int n)
{
    Graph G = malloc(sizeof(GraphObj));
    G->size = 0;
    G->verts = n;
    G->arr = malloc((n+1)*sizeof(List));
    G->discover = malloc((n+1)*sizeof(int));
    G->finish = malloc((n+1)*sizeof(int));
    G->parent = malloc((n+1)*sizeof(int));
    G->color = malloc((n+1)*sizeof(char));
    int i;
    for(i = 0; i <= n; i++)
    {
        G->arr[i] = newList(); // TODO: Be sure to test to see if this is necessary
        G->parent[i] = NIL; // set all predessors to NIL
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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

int getParent(Graph G, int u) //Get parent of u in G
{
    if(G == NULL || u < 1 || u > getOrder(G))
        return NIL;
    return G->parent[u];
}

int getDiscover(Graph G, int u)
{
    if(u < 1 || u > getOrder(G))
        return UNDEF;
    return G->discover[u];
}

int getFinish(Graph G, int u)
{
    if(u < 1 || u > getOrder(G))
        return UNDEF;
    return G->finish[u];
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
    free((*pG)->discover);
    free((*pG)->color);
    free((*pG)->finish);
    free((*pG)->parent);
    free((*pG)->arr);
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
        //For this version of Graph.c, to work with the tester
        //supplied by Isaak(TA), we are now printing empty Lists
        //so the commented lines ignore empty Lists, which now is
        //no long the cases.
//        if(length(G->arr[i]) != 0)
        fprintf(out,"%i: ",i);
        printList(out,G->arr[i]);
        if( getOrder(G) != i) //length(G->arr[i]) != 0 &&
            fprintf(out,"\n");
    }
}

void visit(Graph G, int v, List S) //v is the vertex in question
{
    G->color[v] = 'g';
    G->discover[v] = ++G->time;
    moveFront(G->arr[v]);
    while(index(G->arr[v]) >= 0)
    {
        int y = get(G->arr[v]);
        if(G->color[y] == 'w')
        {
            G->parent[y] = v;
            visit(G, y, S);
        }
        moveNext(G->arr[v]);
    }
    G->color[v] = 'b';
    G->finish[v] = ++G->time;
    prepend(S, v);
}

void DFS(Graph G, List S)    /* TODO Pre: length(S)==getOrder(G) */
{
    //Precondition to make sure all vertices
    if(length(S) != getOrder(G))
    {
        printf("DFS::length(S) != getOrder(G)");
        return;
    }
    int i, x;  //i is a for loop counter; x is a temp for stack.
    for(i = 1; i <= getOrder(G); i++)
    {
        G->parent[i] = NIL;
        G->color[i] = 'w';
    }
    G->time = 0;
    moveFront(S);
    while(index(S)>=0)
    {
        x = get(S);
        if(G->color[x] == 'w')
        {
            visit(G,x, S);
        }
        moveNext(S);
    }
    //delete the elements that came with the input
    for(i = 1; i <= getOrder(G); i++)
        deleteBack(S);

        printfinish(G);
}


void printfinish(Graph G)
{
    int i=1;
    printf("\nPrint Finish Arry:\n");
    for(; i<= getOrder(G); i++)
        printf("finish[%d] = %d\n",i,G->finish[i]);
    printf("\nPrint Discover Array:\n");
    for(i=1; i<= getOrder(G); i++)
        printf("Discover[%d] = %d\n",i,G->discover[i]);
    for(i=1; i<= getOrder(G); i++)
        printf("parent[%d] = %d\n",i,G->parent[i]);
}


Graph copyGraph(Graph G) //copy G to G2
{
    if(G == NULL)
        return NULL;
    Graph G2 = newGraph(getOrder(G));
    int i;
    /*
    Each graph consists a Array of List, since copyList is already
    implemented to copy Lists, the loop below uses it to copy each list
    from G to G2;
    */
    for(i = 1; i <= getOrder(G); i++)
    {
        G2->arr[i] = copyList(G->arr[i]);
    }
    return G2;
}


Graph transpose(Graph G) //Transpose G to G2
{
    if(G == NULL)
        return NULL;
    Graph G2 = newGraph(getOrder(G));
    int i;
    for(i = 1; i <= getOrder(G); i++)
    {
        /*The transpose in this representation is basically
        swapping the u with the v in addArc, thus the loop
        goes through the entire graph, taking each row number
        as the v and each element in it to be the u*/
        moveFront(G->arr[i]);
        while(index(G->arr[i])>=0)
        {
            addArc(G2,get(G->arr[i]), i);
            moveNext(G->arr[i]);
        }
    }
    return G2;
}
