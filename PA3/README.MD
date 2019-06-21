Tyler Hu
qhu27
1575112
10/30/2017

Programming Assignment 3 Professor Patrick Tantalo

Third assignment of the quarter, this assignment consists of 3 main files Sparse.java and List.java, Matrix.java. They come with a Makefile for easy compiling.

List.java - A deque used to represent the rows of the Matrix; it has been modified to take Objects, so other data types besides ints can be pasted in now

Matrix.java - Data Type used to represent a sparse Matrix, List.java is used to represent a row of a matrix. It can add, sub, transpose, multiply and be multiply with a constant. 

Sparse.java - Takes in 2 parameters, one for the input and one for the out file. It creates a Matrix from the input and outputs several operations in that perform on that matrix.

ListTest.java - Very simple tester; tests the the main functions of the List class including but not limited to prepend, append, insertBefore, insertAfter, delete, equals, etc with two size 50 list.

MatrixTest - Tester for Matrix.javal; creates a 100x100 Matrix with randomly generated elements, then add, sub, transpose, multiply, and scalar multiplies against two different arrays both 100x100. Results will be printed everytime.

ReadMe - General Information for all files on this project.
