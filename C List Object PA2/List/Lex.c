//-----------------------------------------------------------------------------
// Tyler Hu
// #1597112
// Programming assignment 2
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF 256 /* can change the buffer size as well */
#define TOT 100 /* change to accomodate other sizes, change ONCE here */
#include "List.h"

int getLength(char * x)
{
    FILE * in = fopen(x,"r");
    char line[BUF];
    int length = 0;
    while( fgets(line, BUF, in) != NULL)
    {
        length ++;
        strtok(line, "\n");
    }
    fclose(in);
    return length;
}


int main(int argc, char * argv[])
{
//      check command line for correct number of arguments
//   if( argc != 3 ){
//      printf("Usage: %s <input file> <output file>\n", argv[0]);
//      exit(1);
//   }
//    int size = getLength(argv[1]);
//    char strings[size][BUF];
//    char inputline[100]=""; //cstring to hold temporarily hold each line in the file.
//    FILE *input = fopen(argv[1], "r"); // input file argv[1]
//    FILE *output = fopen(argv[2], "w"); // output file argv[2]


    int size = getLength("input.txt");
    char strings[size][BUF];
    char inputline[100]=""; //cstring to hold temporarily hold each line in the file.
    FILE *input = fopen("input.txt", "r"); // input file argv[1]
    FILE *output = fopen("output.txt", "w"); // output file argv[2]

    int i = 0;
    if(!input || !output)
        printf("stderr");

    while(fgets(inputline, BUF, input)) //continously read from file
    {
        strcpy(strings[i], inputline);
        i++;
    }

    List L1 = newList();
    int x;
    prepend(L1, 0);
		for (i = 1; i < size; i++)
		{
		    moveBack(L1);
            while(index(L1)>=0)
            {
                x = get(L1);
                if(strcmp(strings[i],strings[x]) >= 0)
                {
                    insertAfter(L1,i);
                    break;
                }
                else if(strcmp(strings[i],strings[x]) < 0 && index(L1) == 0)
                {
                    prepend(L1,i);
                    break;
                }
                movePrev(L1);
            }
		}
//    printf("forget me not");
//    printList(output, L1);
   moveFront(L1);
//   printf("%i", index(L1));
   while(index(L1) >= 0)
   {
       fprintf(output, "%s",strings[get(L1)]);
       printf("%s",strings[get(L1)]);
       if(get(L1) == size-1)
       {
        printf("\n");
        fprintf(output, "\n");
       }

       moveNext(L1);
   }

   freeList(&L1);
   fclose(input);
   fclose(output);
   return 0;
}
