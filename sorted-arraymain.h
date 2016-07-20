#ifndef SORTED_ARRAYMAIN_H
#define SORTED_ARRAYMAIN_H
/*
 * sorted-arraymain.h
 */

#include <stdlib.h>
#include "sorted-list.h"

/*
 * Element type.
 */
struct element
{
  // token is the pointer to the char token held by this element.
  char *token;
  // sl is the pointer to the list of files associated with this token.
  struct SortedList *sl;
};
typedef struct element Elem;

/*
 * Sorted list type.  You need to fill in the type as part of your implementation.
 */
struct MainSortedArray
{
  // Size of the array.
  int arraySize;
  // Number of elements actually in the array 
  int numElem;
  // ElemArray is an array of Elements.
  struct element *ElemArray;
};
typedef struct MainSortedArray* MSortedArrayPtr;

/*
 * MSLCreate creates a new, empty main sorted list.  If the function succeeds, 
 * it returns a (non-NULL) MSortedList object, otherwise, it returns NULL.
 */

MSortedArrayPtr MSACreate();

/*
 * MSADestroy destroys an array, freeing all dynamically allocated memory.
 */
 
void MSADestroy(MSortedArrayPtr array);

/*
 * isStart checks to see if the current line is the start.
 * If it succeeds it returns the token associated with this list, otherwise it returns NULL.
 */

int isStart(char *c, MSortedArrayPtr array);

/*
 * isEnd checks to see if the current line is the end.
 * If it succeeds it returns 1, otherwise it returns 0.
 */

int isEnd(char *c);

/*
 * readLine reads in the current line (and tests to make sure it is a valid line) to an 
 * element in an array of Elements. If it succeeds it returns 1, otherwise it returns 0.
 */

int readLine(char *c, SortedListPtr list);

/*
 * readFile reads and creates a sorted array based on the filename of an indexer passed
 * to the function as fn. If it succeeds it returns the array, otherwise it returns NULL.
 */
 
MSortedArrayPtr readFile(char *fn);

#endif
