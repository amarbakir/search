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
 * SLSwap searches throught the list to insert a node being swapped due to a freq change.
 */

void SLSwap(SortedListPtr list, Node *n) {
	Node *curr;
	Node *prev;
	curr = list->front;
	prev = NULL;
	while (curr != NULL) {
		if (curr->freq < n->freq) {
			if(prev == NULL) {
				list->front = n;
				n->next = curr;
				return;
			}
			else{
				prev->next = n;
				n->next = curr;
				return;
			}
		}
		/*
		 * If the current content is "smaller" than the content to be inserted, then
		 * the content to be inserted must come right before the current content.
		 */
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	if (curr == NULL && prev != NULL) {
		prev->next = n;
		n->next = NULL;
		return;
	}
}


/*
 * SLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list. If the function succeeds, 
 * it returns 1, othrewise it returns 0.
 */

int SLInsert(SortedListPtr list, char *newObj) {
  Node *newNode;
  Node *swapNode;
  Node *curr;
  Node *prev;
  char *fn;
  fn = (char *)malloc((strlen(newObj) + 1) * sizeof(char));
  strcpy(fn, newObj);
  curr = list->front;
  prev = NULL;
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
  // If the list is empty just put the node in front.
  if (list->front == NULL) {
    list->front = newNode;
    newNode->freq = 1;
    newNode->next = NULL;
    return 1;
  }
  // Searching through the list to see if this filename exists.
  while (curr != NULL) {
    // If a duplicate is found increment the freq and return 1.
    if (strcmp(curr->filename, newObj) == 0) {
      curr->freq++;
      free(fn);
      free(newNode);
      if (prev != NULL && curr->freq > prev->freq) {
		  swapNode = (Node *)malloc(sizeof(Node));
		  prev->next = curr->next;
		  swapNode->filename = curr->filename;
		  swapNode->freq = curr->freq;
		  SLSwap(list, swapNode);
	  }
      return 1;
    }
    /*
     * Otherwise continue to search the list.
     */
    else {
		prev = curr;
		curr = curr->next;
	}
  }
  /*
   * If you get to the end of the non-empty list then simply add the new node to the end.
   */
  if (curr == NULL && prev != NULL) {
    prev->next = newNode;
    newNode->freq = 1;
    newNode->next = NULL;
    return 1;
  }
  // Otherwise you somehow failed.
  free(fn);
  free(newNode);
  return 0;
}
