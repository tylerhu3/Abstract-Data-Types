Tyler Hu
Cruz ID: qhu27
Student #1597112
Programming assignment 5
Professor Patrick Tantalo

Purpose:
Make a Graph ADT that utilizes prior created List ADT to represent a Graph via
an Array of List. Then find all the SCC(Strongly Connected Components) of that graph

FindComponents.c - This module takes 2 parameters one input file and one output file
it creates a graph ADT from the input and then performs DFS and finds all the
SCC(Strongly Connected Components) of the inputted Graph and outputs it to the outputfile.

List.c - A deque used to represent the adjacency list of each row of Graph

List.h - Header file for List.c

Graph.c -  Graph ADT Implementation; make array of n List objects where each
List represents the connected connected components from n to the item inside each
List. Compared to the previous assignment, there's no longer a BFS function, its now
replaced with DFS. Also transposed and copyGraph is included, for transposing a graph
and copying a graph.

GraphTest.c - Isolated Test to test all of Graph.c's functions.

Graph.h - Header file for Graph.c

ReadMe - General Information for all files on this project.


Makefile - Script file used to compiled the c files in this assignment
