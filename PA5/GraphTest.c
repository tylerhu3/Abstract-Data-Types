//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 5
// This is a isolated test of Graph.c's functions
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include "Graph.h"
#include "List.h"
void printfinish(Graph G)
{
    int i=1;
    printf("\nPrint Finish Arry:\n");
    for(; i<= getOrder(G); i++)
        printf("finish[%d] = %d\n",i,getFinish(G, i));
    printf("\nPrint Discover Array:\n");
    for(i=1; i<= getOrder(G); i++)
        printf("Discover[%d] = %d\n",i,getDiscover(G,i));
    printf("\nParents Discover Array:\n");
    for(i=1; i<= getOrder(G); i++)
        printf("Parent[%d] = %d\n",i,getParent(G,i));
}
int main(){

    printf("Welcome to GraphTest, if any test should fail,\na print statement will notified you of the failed\ntest followed by what the test was. Otherwise just \nthe graph and it's arrays will be printed\n");
    int graphSize = 5;
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
    addArc(G1,2,3);
    addArc(G1,3,1);
    addArc(G1,3,4);
    addArc(G1,4,5);
    //Test to make sure same edges aren't added more than once
    printf("Printing Graph\n");
    printGraph(stdout, G1);
    printf("\n");
    if(getSize(G1) != 5)
    {
        printf("Fail Test 3: adding the same edges\n");
    }

    int i;
    List A1 = newList();
     for(i = 1; i<= getOrder(G1); i++)
        append(A1,i);

    DFS(G1,A1); //Perform DFS with the List just numbered ordered List just created
    printf("Printing Graph Arrays:\n");
    printfinish(G1); //prints the finished arrays of G2
    if(getFinish(G1,1) != 10)
    {
        printf("Failed Test 4: Checking finish");
    }
    if(getDiscover(G1,4) != 4)
    {
        printf("Failed Test 5: Checking discover");
    }

    if(getParent(G1,4) != 3)
    {
        printf("Failed Test 6: Checking parent");
    }

    Graph G2 =transpose(G1);
    printf("\nPrinting transpose Graph\n");
    printGraph(stdout,G2);
    Graph G3 = copyGraph(G2);
    printf("\nPrinting copy of transpose Graph\n");
    printGraph(stdout, G3);

    printf("\n\nPrinting Transpose Graph Arrays:\n");
    printfinish(G2);  //prints the finished arrays of G2


   return 70;
}
