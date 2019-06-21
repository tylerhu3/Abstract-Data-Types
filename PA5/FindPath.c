//-----------------------------------------------------------------------------
// Tyler Hu
// Cruz ID: qhu27
// Student #1597112
// Programming assignment 4
// FindPath.c - This module takes 2 parameters one input file and one output file
// it creates a graph ADT from the input and then finds the shortest path from
// the desired source to destination and then all the information is written to the
// the output file.
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char * argv[])
{

//    if( argc != 3 ) //Incorrect amount of arguments; EXIT
//    {
//        printf("Usage: %s <input file> <output file>\n", argv[0]);
//        exit(91);
//    }
//    FILE *input = fopen(argv[1], "r"); // input file
//    FILE *output = fopen(argv[2], "w"); // output file

Test Files
    FILE *input = fopen("infile1.txt", "r"); // input file argv[1]
    FILE *output = fopen("output.txt", "w"); // output file argv[2]

    if(!input || !output) //If either of the file handlers aren't opened correctly exit.
    {
        printf("Files not opened properly");
        exit(911);
    }

    int size, i = 0, row = 0, col = 0; //temp variables to store processing numbers
    fscanf(input, "%d", &size); // get size for the Graph ADT
    Graph G1 = newGraph(size); // ADT to represent graph in the for of a ADJ List
    List A1 = newList(); // This will hold the shortest route from source to Destination

    //Part 1: Create ADJ List Graph
    while(1)
    {
        fscanf(input, "%d", &row); //process row
        fscanf(input, "%d", &col); //process col
        if(row == 0) // if any of the processed numbers are 0 exit loop
        {
            break;
        }
        addEdge(G1, row, col); //add the edges between row and col
        i++;
    }
    printGraph(output,G1); //print Graph to output file

    //Part 2: get the source to destinations
    //In this scenario variable row is used to hold SOURCE and variable col is DESTINATION
    while(1)
    {
        fscanf(input, "%d", &row); //processed source
        fscanf(input, "%d", &col); //processed destination
        if(row == 0)  // if any of the processed numbers are 0 exit loop
        {
            break;
        }
        BFS(G1, row); // perform BFS on source row
        getPath(A1, G1, col); // get path from row to col
        fprintf(output,"\n\n");
        fprintf(output,"The distance from %d to %d is ", row, col);
        if(getDist(G1, col) < 0) //If Distance is less than 0 -> INF
        {
            fprintf(output,"infinity\n");
            fprintf(output,"No %d-%d path exists",row,col);
        }
        else // Processed the print normally
        {
            fprintf(output,"%d",getDist(G1, col));
            fprintf(output,"\nA shortest %d-%d path is: ",row,col);
            printList(output, A1);
        }
        clear(A1); //Clear the list for the next iteration
        i++;
    }

    fclose(input);
    fclose(output);
    return 0;
}
