#include "sorted-list.h"
#include <string.h>


/*
 * SLCreate creates a new, empty sorted list.  If the function succeeds, 
 * it returns a (non-NULL) SortedListT object, otherwise, it returns NULL.
 */

SortedListPtr SLCreate() {
  // Creating and mallocing the sl to be returned via the pointer sl.
  SortedListPtr sl;
  sl = (struct SortedList *)malloc(sizeof(struct SortedList));
  // If malloc fails print an error statement and return NULL.
  if (sl == NULL) {
    //printf("Error: Out of memory.\n");
    return NULL;
  }
  sl->front = NULL;
  sl->back = NULL;
  return sl;
}

/*
 * SLDestroy destroys a list, freeing all dynamically allocated memory.
 */

void SLDestroy(SortedListPtr list) {
  Node *temp;
  // Runs through the entire list, deleting the front node every time through.
  while (list->front != NULL) {
    temp = list->front;
    list->front = list->front->next;
    // Destroying the content pointed to by the node and then freeing the node.
    free(temp->filename);
    free(temp);
  }
  // Freeing the list after we destroy all the nodes.
  free(list);
}

/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list. If the function succeeds, 
 * it returns 1, otherwise it returns 0.
 */

int SLInsert(SortedListPtr list, char *newObj, long freq) {
  Node *newNode;
  char *fn;
  fn = (char *)malloc((strlen(newObj) + 1));
  strcpy(fn, newObj);
  fn[strlen(newObj)] = '\0';
  // Creating the node to be inserted.
  newNode = (Node *)malloc(sizeof(Node));
  // If malloc fails print an error statement and return 0.
  if (newNode == NULL) {
    //printf("Error: Out of memory.\n");
    free(fn);
    free(newNode);
    return 0;
  }
  // Set the values of the new node.
  newNode->filename = fn;
  newNode->freq = freq;
  // If the list is empty just put the node in front.
  if (list->front == NULL) {
    list->front = newNode;
  }
  // Otherwise add the node to the back of the list. 
  else {
	list->back->next = newNode;
  }
  list->back = newNode;
  newNode->next = NULL;
  return 1;
}
