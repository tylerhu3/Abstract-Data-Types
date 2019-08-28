//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 4
// This is a isolated test of Graph.c's functions
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "Graph.h"
#include "List.h"

int main(){
    srand(time(NULL)); // will be generating random numbers to create a random connected Graph
//
//    for(int i = 0; i < 50; i++)
//        printf("%d\n",rand() % 20 +1);

    int graphSize = 50;
    Graph G1 = NULL;
    if(getSize(G1) != 0)
    {
        printf("Failed Test 1: getSize @ NULL initialization\n");
    }

    G1 = newGraph(graphSize);
    if(getOrder(G1) != graphSize)
    {
        printf("Failed Test 2: getOrder of Graph size, %d \n", graphSize);
    }
    addArc(G1,1,2);
    addArc(G1,1,2);
    addArc(G1,2,3);
    addArc(G1,1,3);
    //Test to make sure same edges aren't added more than once
    if(getSize(G1) != 3)
    {
        printf("Fail Test 3: adding the same edges\n");
    }

    BFS(G1, 1);
    printf("Graph print: \n");
    if(getParent(G1, 2) != 1)
    {
        printf("Test 4 Failed\n");
    }

    if(getParent(G1, 3) != 1)
    {
        printf("Test 5 Failed\n");
    }

    printGraph(stdout,G1);

    if(getSource(G1) != 1)
    {
        printf("Failed Test 6\n");
    }

    List A1 = newList();
    List A2 = newList();
    append(A2,1);
    append(A2,3);
    getPath(A1, G1, 3);

    if(!equals(A1,A2))
    {
        printf("\nTest 7 failed\n");
    }

    makeNull(G1);
    printf("\nIf anything is prevented below makeNull() failed:\n");
    printGraph(stdout,G1);

   return 70;
}
