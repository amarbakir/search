#include "sorted-listmain.h"
#include <string.h>


/*
 * MSLCreate creates a new, empty main sorted list.  If the function succeeds, 
 * it returns a (non-NULL) MSortedListT object, otherwise, it returns NULL.
 */

MSortedListPtr MSLCreate() {
  // Creating and mallocing the sl to be returned via the pointer sl.
  MSortedListPtr sl;
  sl = (struct MainSortedList *)malloc(sizeof(struct MainSortedList));
  // If malloc fails print an error statement and return NULL.
  if (sl == NULL) {
    //printf("Error: Out of memory.\n");
    return NULL;
  }
  sl->front = NULL;
  return sl;
}

/*
 * MSLDestroy destroys a list, freeing all dynamically allocated memory.
 */
 
void MSLDestroy(MSortedListPtr list) {
  MNode *temp;
  // Runs through the entire list, deleting the front node every time through.
  while (list->front != NULL) {
    temp = list->front;
    list->front = list->front->next;
    // Destroying the content pointed to by the node and then freeing the node.
    free(temp->token);
    SLDestroy(temp->sl);
    free(temp);
  }
  // Freeing the list after we destroy all the nodes.
  free(list);
}


/*
 * MSLInsert inserts a given object into a sorted list, maintaining sorted
 * order of all objects in the list. If the item is already in the list, it acts
 * as a search function. If the function succeeds, it returns  a pointer to the 
 * found or inserted node, othrewise it returns NULL.
 */

MNode *MSLInsert(MSortedListPtr list, char *newObj) {
  MNode *newNode;
  MNode *curr;
  MNode *prev;
  char *tk;
  tk = (char *)malloc((strlen(newObj) + 1) * sizeof(char));
  strcpy(tk, newObj);
  curr = list->front;
  prev = NULL;
  // Creating the node to be inserted.
  newNode = (MNode *)malloc(sizeof(MNode));
  // If malloc fails print an error statement and return 0.
  if (newNode == NULL) {
    //printf("Error: Out of memory.\n");
    free(tk);
    free(newNode);
    return 0;
  }
  // Set the values of the new node.
  newNode->token = tk;
  // If the list is empty just put the node in front.
  if (list->front == NULL) {
    list->front = newNode;
    newNode->sl = SLCreate();
    newNode->next = NULL;
    return newNode;
  }
  // Searching through the list for the correct position of the new node.
  while (curr != NULL) {
    // If a duplicate is found simply return a pointer to the duplicate item.
    if (strcmp(curr->token, newObj) == 0) {
      //printf("Error: Duplicate value insertion.\n");
      free(tk);
      free(newNode);
      return curr;
    }
    /*
     * If the current content is "bigger" than the content to be inserted, then
     * the content to be inserted must come right before the current content.
     */
    else if (strcmp(curr->token, newObj) > 0) {
      // Check to see if the new node is to be put in the front of the list.
      if (prev == NULL) {
		list->front = newNode;
		newNode->sl = SLCreate();
		newNode->next = curr;
		return newNode;
      }
      // Otherwise just insert the new node.
      else {
		prev->next = newNode;
		newNode->sl = SLCreate();
		newNode->next = curr;
		return newNode;
      }
    }
    /*
     * If the current content is "smaller" than the content to be inserted, then
     * simply continue, for the correct position must be somewhere after the
     * current node.
     */
    else {
      prev = curr;
      curr = curr->next;
    }
  }
  /*
   * If you get to the end of the non-empty list and all the content was smaller,
   * then just throw the new node at the end (it is bigger than everything else
   * in the list.
   */
  if (curr == NULL && prev != NULL) {
    prev->next = newNode;
    newNode->sl = SLCreate();
    newNode->next = curr;
    return newNode;
  }
  // Otherwise you somehow failed.
  free(tk);
  free(newNode);
  return NULL;
}
