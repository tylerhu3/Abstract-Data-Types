//-----------------------------------------------------------------------------
// Tyler Hu
// #1597112
// Programming assignment 2
// List.h
// List ADT Implementation
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include "List.h"

// STRUCTS --------------------------------------------------------------------
// private NodeObj type
typedef struct NodeObj
{
    int data;
    struct NodeObj* prev;
    struct NodeObj* next;
} NodeObj;

// private Node type
//This will allow future assignemnts to just being Node variable name
//otherwise you'll have to type struct NodeObj *front every single time
typedef NodeObj* Node;

// private List type
typedef struct ListObj
{
    Node front;
    Node back;
    Node cursor;
    int length,index;
} ListObj;


// CONSTRUCTOR-DESTRUCTORS ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
    Node node = malloc(sizeof(NodeObj));
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return(node);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
    if( pN!=NULL && *pN!=NULL )
    {
        (*pN)->next = (*pN)->prev = NULL;
        free(*pN);
        *pN = NULL;
    }
}

// newList()
// Returns reference to new empty Queue object.
List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}
// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S


int isEmpty(List L)
{
    if( L==NULL )
    {
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(1);
    }
    return(L->length==0);
}

void freeList(List* L)
{
    if(*L == NULL)
        return;

    if(length(*L) == 0)
        return;

    clear(*L);
    free(*L);
    *L = NULL;

}

void clear(List L)
{
    moveFront(L);
    while(length(L)>0)
    {
        deleteFront(L);
        moveFront(L);
    }

}

void deleteFront(List L)  // Deletes element at front of L
{
    if( L==NULL || length(L) == 0)
    {
        return;
    }

    Node N = NULL;
    N = L->front;
    if(L->front == L->cursor)
    {
        L->cursor =  NULL;
        L->index = -1;
    }
    if(length(L) > 1)
    {
        L->front = L->front->next;
        L->index--;
    }
    else
    {
        L->front = L->back = L->cursor =  NULL;
    }
    L->length--;
    freeNode(&N);
}
//ACCESS FUNCTIONS ----------------------------------------------------------

// length()
// Returns true (1) if L is empty, otherwise returns false (0)


int get(List L) // Returns cursor element. Pre: length()>0, index()>=0
{
    if (L->length <= 0 || index(L) < 0)
    {
//			cout("get()::length() <= 0 || index() < 0");
        return -1;
    }
    return(L->cursor->data);
}

int front(List L) // Returns front element. Pre: length()>0
{
    if( L==NULL )
    {
        printf("Lueue Error: calling getFront() on NULL Lueue reference\n");
        exit(1);
    }
    if( length(L) == 0)
    {
        printf("Lueue Error: calling getFront() on an empty Lueue\n");
        exit(1);
    }
    return(L->front->data);
}

int back(List L) // Returns rear element. Pre: length()>0
{
    if( L==NULL )
    {
        printf("Lueue Error: calling getFront() on NULL Lueue reference\n");
        exit(1);
    }
    if(length(L) == 0 )
    {
        printf("Lueue Error: calling getFront() on an empty Lueue\n");
        exit(1);
    }

    return(L->back->data);
}

int index(List L) //If cursor is defined, returns the index of the cursor element
{
    if(L->cursor != NULL)
    {
        return (L->index);
    }
    return -1; //if cursor is pointed towards NULL
}

int length(List L) // Returns the length of L.
{
    if( L==NULL )
    {
        printf("List Error: calling length() on NULL List reference\n");
        return 0;
    }
    return(L->length);
}

int equals(List A, List B)
{
    moveFront(A);
    moveFront(B);

    while(index(A) >= 0 || index(B) >= 0)
    {
        if(get(A) != get(B))
        {
            return 0;
        }
        moveNext(A);
        moveNext(B);
    }
    return 1;
}

//MANIPULATORS -----------------------------------------------------------------

void moveFront(List L) //move cursor to the front
{
    if (L->length == 0)
    {
        return;
    }
    L->cursor = L->front;
    L->index = 0;
}

void moveBack(List L) //move cursor to the front
{
    if (L->length == 0)
    {
        return;
    }
    L->cursor = L->back;
    L->index = L->length -1 ;
}



void deleteBack(List L)
{
    if( L==NULL || length(L) == 0)
    {
        return;
//        printf("List Error: calling deleteFront() on NULL List or length() reference\n");
//        exit(1);
    }

    Node N = NULL;
    N = L->back;
    if(L->back == L->cursor)
    {

        L->cursor = 0;
    }
//    }
    if( length(L) >1 )
    {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else
    {
        L->front = L->back = NULL;
    }
//    printf("N pointer: %i \n", N);
    freeNode(&N);
//    printf("N pointer: %i \n", N);
    L->length--;
}
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void append(List L, int data) // Places new data element at the start of List
{

    if( L==NULL )
    {
        printf("List Error: calling append() on NULL List reference\n");
        return;
    }
    Node N = newNode(data);
    if( length(L) == 0)
    {
        L->front = L->back = N;

    }
    else
    {

        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

void moveNext(List L)
{
    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    if (L->cursor == NULL)
    {
        return;
    }

    L->cursor = L->cursor->next;
    L->index++;
}

void movePrev(List L)
{
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    if (L->cursor == NULL)
    {
        return;
    }
    L->cursor = L->cursor->prev;
    L->index--;
//		cout("cursor != null and index: " + index + " cursor : " + cursor);

}

void prepend(List L, int data) // Places new data element at the start of List
{
    if( L==NULL )
    {
        printf("List Error: calling append() on NULL List reference\n");
        return;
    }

    Node N = newNode(data);
    if( length(L) == 0 )
    {
        L->front = L->back = N;
    }
    else
    {

        L->front->prev = N;
        N->next = L->front;
        N->prev = NULL;
        L->front = N;
        L->index++;
    }
    L->length++;
}

void insertBefore(List L, int data)
{
    if (length(L) <= 0 || index(L) < 0)
    {
        return;
    }
    if(L->cursor == L->front)
    {
        prepend(L,data);
        return;
    }
    Node N = newNode(data);
    N->prev = L->cursor->prev;
    L->cursor->prev->next = N;
    L->cursor->prev = N;
    N->next = L->cursor;
    L->length++;
    L->index++;
}



void insertAfter(List L, int data)
{
    if (length(L) <= 0 || index(L) < 0)
    {
        return;
    }
    if(L->cursor == L->back)
    {
        append(L,data);
        return;
    }
    Node N = newNode(data);
    N->next= L->cursor->next;
    L->cursor->next->prev = N;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length++;
}
void printList(FILE* out, List L)
{
    Node N = NULL;
    if( L==NULL )
    {
        printf("List Error: calling printList() on NULL List reference\n");
        return;
    }
    moveFront(L);
    for(N = L->front; N != NULL; N = N->next)
    {
//        printf("%i", N->data);
        fprintf(out, "%i", N->data);
        if(index(L)!= (length(L)-1))
        {
//            printf("\n %i <- index length-1 -> %i \n",index(L), (length(L)-1));
            fprintf(out, " ");
//            printf(" ");
        }
        moveNext(L);
    }
}

void delete(List L)
{
    if(L->cursor == NULL)
    {
        return;
    }
    if(L->cursor == L->front)
    {
        L->index = -1;
        deleteFront(L);
        return;
    }
    if(L->cursor == L->back)
    {
        L->index = -1;
        deleteBack(L);
        return;
    }
    L->length--;
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    freeNode(&L->cursor);
    L->index = -1;
}

List copyList(List L)
{
    if(L == NULL)
    {
        exit(1);
    }
    List A = newList();
    Node temp = L->cursor;
    int tempIndex = L->index;
    moveFront(L);
    while(index(L)>=0)
    {
        append(A, get(L));
        moveNext(L);
    }
    L->cursor = temp;
    L->index = tempIndex;
    return (A);
}
