Tyler Hu

10/1/2017

Programming Assignment 2
Professor Patrick Tantalo



Secoond assignment of the quarter, this assignment consists of 2 main files Lex.c and List.c. They come with a Makefile for easy compiling. The program takes 2 parameters as
input. The first parameter is a input text file and then second parameter is the output file name. Lex takes input file sorts it into the  ADT List and it gets outputted to the output
file in ABC order.

Command line EX: Lex input.txt output.txt



Lex.c - Main running client. Takes input and output; has function for finding size of input, the core work is in a loop that works similar to insertion sort, putting the correct
element in ABC order into List.



List.c - Very simliar to doubly queue with additional functions. It allows the client to move a cursor along the queue, all the while giving the ability to insert in any location.



Makefile - Script file used to compiled the c files in this assignment


ListClient.c - Test file for Lex and List.