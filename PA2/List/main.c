#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF 128 /* can change the buffer size as well */
#define TOT 100 /* change to accomodate other sizes, change ONCE here */
#include"List.h"

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

int main(int argc, char * argv[])
{
    int size = getLength("input.txt");
    char* pstring; //pointer to tokenized word
    char strings[size][BUF];
    char inputline[100]=""; //cstring to hold temporarily hold each line in the file.
    FILE *input = fopen("input.txt", "r");
    int i = 0;
    if(!input)
        printf("stderr");
    while(fgets(inputline, BUF, input)) //continously
    {
        pstring = strtok (inputline, "\n"); //parses the input line to remove \n
        strcpy(strings[i], pstring);
        i++;
    }

    for(i = 0; i < size; ++i)
        printf("%s\n", strings[i]);
    /* close files */
   fclose(input);

   List L1 = newList();

   append(L1, 1);
   append(L1, 2);
   append(L1, 3);
   append(L1, 4);
   append(L1, 5);
   prepend(L1, 79);
   printList(L1);
    int x = front(L1) , y = back(L1);
    printf("front: %i back: %i length %i \n" , x , y , length(L1));
    moveBack(L1);
    printf("cursor index: %i get: %i", index(L1), get(L1));
    return 0;
}
