//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 5
// FindComponents.c - This module takes 2 parameters one input file and one output file
// it creates a graph ADT from the input and outputs the Adjacency list representation
// of the graph, and the strongly connected components into the output file
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[])
{
    if( argc != 3 ) //Incorrect amount of arguments; EXIT
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(91);
    }
    FILE *input = fopen(argv[1], "r"); // input file
    FILE *output = fopen(argv[2], "w"); // output file

    int size, i = 0, row = 0, col = 0; //temp variables to store processing numbers
    int k = 0; //used to hold the total SCC of G1
    fscanf(input, "%d", &size); // get size for the Graph ADT
    Graph G1 = newGraph(size); // ADT to represent graph in the for of a ADJ List
    List A1 = newList(); // This will be the Stack for DFS

    //Part 1: Create ADJ List Graph
    while(1)
    {
        fscanf(input, "%d", &row); //process row
        fscanf(input, "%d", &col); //process col
        if(row == 0) // if any of the processed numbers are 0 exit loop
        {
            break;
        }
        addArc(G1, row, col); //add the edges between row and col
        i++;
    }
    fprintf(output,"Adjacency list representation of G:\n");
    printGraph(output,G1); //print Graph to output file
    fprintf(output,"\n");

    //Create Lists of the vertices in ascending order for processing
    for(i = 1; i<= getOrder(G1); i++)
        append(A1,i);

    DFS(G1,A1); //Perform DFS with the List just numbered ordered List just created
    Graph G2 = transpose(G1); //Let G2 be the transpose of G1
    DFS(G2,A1); //Perform DFS G2 with finished A1 which now has vertices in  reversed
    //finished number order
    for(i = 1; i <= getOrder(G2); i++) //Find total number of SCC by looking for NIL parents
    {
        if(getParent(G2,i) == NIL)
            k++;
    }
    List* orderSCC = malloc((k)*sizeof(List)); //List Array for each SCC
    for(i = 0; i < k; i++) //create each List
        orderSCC[i] = newList();
    fprintf(output,"\nG contains %d strongly connected components: \n", k);
    //printf("\nG contains %d strongly connected components: \n", k);
    moveFront(A1);

    /*
    Below is just the code to put each SCC into a separate list
    that way I can print it as per the prompt of this assignment,
    it's not the most elegant solution but it's a solution.
    */
    for(i = k-1; i >= 0; i--)
    {
        int x = get(A1);
        do
        {
            x = get(A1);
            append(orderSCC[i],x);
            moveNext(A1);
        }
        while(getParent(G2,get(A1)) >= 0);
    }
    //prints each list as per the assignment prompt
    for(i = 0; i < k; i++)
    {
        fprintf(output,"Component %d: ",i+1);
        printList(output,orderSCC[i]);
        if(i != k-1) //no more newline if we are at the last print
        {
            fprintf(output,"\n");
        }
        freeList(&orderSCC[i]); //free the Lists used after each print
    }
    //Free all previous malloc's in this program
    free(orderSCC);
    freeGraph(&G2);
    freeGraph(&G1);
    freeList(&A1);
    fclose(input);
    fclose(output);
    return 0;
}
