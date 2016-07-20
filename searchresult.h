#ifndef SEARCHRESULT_H
#define SEARCHRESULT_H
/*
 * searchresult.h
 */

#include <stdlib.h>

/*
 * Search result node.
 */
 
struct snode
{
  // filename is the pointer to the filename held in this node.
  char *filename;
  // numFound is the number of times the file has been found
  int numFound;
  // next is the pointer to the next node.
  struct snode *next;
};
typedef struct snode SNode;

/*
 * Search result list.
 */
 
struct SearchResult
{
  // front is a pointer to the start of the list.
  struct snode *front;
  // end is a pointer to the back of the list.
  struct snode *back;
};
typedef struct SearchResult* SearchResultPtr;
	
/*
 * SRCreate creates a new, empty search result list.  If the function succeeds, 
 * it returns a (non-NULL) SearchResultPtr object, otherwise, it returns NULL.
 */
 
SearchResultPtr SRCreate();

/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 */
 
void SRDestroy(SearchResultPtr list);

/*
 * SRInsert inserts a given object into a search result list, ensuring there are no duplicates.
 * If the function succeeds, it returns 1, otherwise it returns 0.
 */

int SRInsert(SearchResultPtr list, char *newObj);

/*
 * output prints out the results of the search, depending on the search mode.
 */
 
void output(SearchResultPtr list, int mode, int maxfind);

#endif
