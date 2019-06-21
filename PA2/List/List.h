//-----------------------------------------------------------------------------
// Tyler Hu
// #1597112
// Programming assignment 2
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type --------------------------------------------------------------

typedef struct ListObj* List;
// Constructors-Destructors ---------------------------------------------------

List newList(void); // Returns reference to new empty List object.
void freeList(List* pL);  // Frees all heap memory associated with List *pL, and sets *pL to NULL.
 // Frees all heap memory associated with List *pL, and sets *pL to NULL.

// Access functions -----------------------------------------------------------
int front(List L);// Returns the value at the front of List.
int back(List L); //returns element in rear
int index(List L); // returns element cursor is pointed towards
int get(List L); // Returns cursor element. Pre: length()>0, index()>=0
int length(List L);// getLength()
int isEmpty(List L);//Check if list empty
int equals(List A, List B); // checks whether List A and B are equal in content
// Manipulation procedures ----------------------------------------------------
void deleteBack(List L); // delete rear element
void moveFront(List L); //move cursor to the front
void moveBack(List L); //move cursor to back end element
void append(List L, int data);//add to back of List
void prepend(List L, int data);//add to front of List
void deleteFront(List L); // Delete element at front of list
void movePrev(List L); // move cursor one element prior
void moveNext(List L); // move cursor to next element
void insertBefore(List L, int data); //insert item before cursor
void insertAfter(List L, int data); //insert item after cursor
void delete(List L); //deletes the element the cursor is currently pointed towards
void clear(List L);
///Print
void printList(FILE* out, List L);
List copyList(List L);

#endif
