#ifndef SORTED_LISTMAIN_H
#define SORTED_LISTMAIN_H
/*
 * sorted-listmain.h
 */

#include <stdlib.h>
#include "sorted-list.h"

/*
 * Node type.
 */
struct mnode
{
  // content is the pointer to the data held by this node.
  char *token;
  // list is the pointer to the list of files associated with this token.
  struct SortedList *sl;
  // next is the pointer to the next node.
  struct mnode *next;
};
typedef struct mnode MNode;


/*
 * Sorted list type.  You need to fill in the type as part of your implementation.
 */
struct MainSortedList
{
  // front is a pointer to the start of the list.
  struct mnode *front;
};
typedef struct MainSortedList* MSortedListPtr;


/*
 * MSLCreate creates a new, empty main sorted list.  If the function succeeds, 
 * it returns a (non-NULL) MSortedListT object, otherwise, it returns NULL.
 */

MSortedListPtr MSLCreate();

/*
 * MSLDestroy destroys a list, freeing all dynamically allocated memory.
 */
 
void MSLDestroy(MSortedListPtr list);


/*
 * MSLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list. If the item is already in the list, it acts
 * as a search function. If the function succeeds, it returns  a pointer to the 
 * found or inserted node, othrewise it returns NULL.
 */

MNode *MSLInsert(MSortedListPtr list, char *newObj);

#endif
