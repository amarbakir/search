#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */

#include <stdlib.h>

/*
 * Node type.
 */
 
struct node
{
  // filename is the pointer to the filename held in this node.
  char *filename;
  // freq is the frequency of the token in this file
  long freq;
  // next is the pointer to the next node.
  struct node *next;
};
typedef struct node Node;

/*
 * Sorted list type.
 */
 
struct SortedList
{
  // front is a pointer to the start of the list.
  struct node *front;
  // end is a pointer to the back of the list.
  struct node *back;
};
typedef struct SortedList* SortedListPtr;
	
/*
 * SLCreate creates a new, empty sorted list.  If the function succeeds, 
 * it returns a (non-NULL) SortedListT object, otherwise, it returns NULL.
 */
 
SortedListPtr SLCreate();

/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 */
 
void SLDestroy(SortedListPtr list);

/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list. If the function succeeds, 
 * it returns 1, othrewise it returns 0.
 */

int SLInsert(SortedListPtr list, char *newObj, long freq);

#endif
