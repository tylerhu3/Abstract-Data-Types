/*
Tyler Hu #1597112
10/1/2017
Programming Assignment 2
*/
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
        strtok(line, " \n");
    }
    return length;
}

int test()
{
   List A = newList();
   List B = newList();
   List C = NULL;
   int i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   }

   printList(stdout,A);
   printf("\n");
   printList(stdout,B);
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); // at index 5
   insertBefore(A, -1);            // at index 6
   for(i=0; i<9; i++) moveNext(A); // at index 15
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); // at index 10
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

//   freeList(&A);
//   freeList(&B);
//   freeList(&C);

   return(0);
}

int main(int argc, char * argv[])
{
     // check command line for correct number of arguments
//   if( argc != 3 ){
//      printf("Usage: %s <input file> <output file>\n", argv[0]);
//      exit(1);
//   }
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
//    for(i = 0; i < size; ++i)
//        printf("%s", strings[i]);

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
//
//moveFront(L1);
//while(index(L1) >= 0)
//{
//    x= get(L1);
//    printf("%s", strings[x]);
//    moveNext(L1);
//}
printf("List: ");
printList(output, L1);
printf("\nFree List\n");
freeList(&L1);
printf("final printing \n");
printList(output, L1);
//    /* close files */
//    freeList(&L1);
test();
   fclose(input);
   fclose(output);
   return 0;
}
