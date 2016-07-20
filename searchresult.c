#include "searchresult.h"
#include <string.h>
#include <stdio.h>


/*
 * SRCreate creates a new, empty search result list.  If the function succeeds, 
 * it returns a (non-NULL) SearchResultPtr object, otherwise, it returns NULL.
 */

SearchResultPtr SRCreate() {
  // Creating and mallocing the sl to be returned via the pointer sl.
  SearchResultPtr sr;
  sr = (struct SearchResult *)malloc(sizeof(struct SearchResult));
  // If malloc fails print an error statement and return NULL.
  if (sr == NULL) {
    //printf("Error: Out of memory.\n");
    return NULL;
  }
  sr->front = NULL;
  sr->back = NULL;
  return sr;
}

/*
 * SRDestroy destroys a search list, freeing all dynamically allocated memory.
 */

void SRDestroy(SearchResultPtr list) {
  SNode *temp;
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
 * SRInsert inserts a given object into a search result list, ensuring there are no duplicates.
 * If the function succeeds, it returns 1, otherwise it returns 0.
 */

int SRInsert(SearchResultPtr list, char *newObj) {
  SNode *newNode;
  SNode *curr;
  char *fn;
  curr = list->front;
  fn = (char *)malloc((strlen(newObj) + 1));
  strcpy(fn, newObj);
  fn[strlen(newObj)] = '\0';
  // Creating the node to be inserted.
  newNode = (SNode *)malloc(sizeof(SNode));
  // If malloc fails print an error statement and return 0.
  if (newNode == NULL) {
    //printf("Error: Out of memory.\n");
    free(fn);
    return 0;
  }
  // Set the values of the new node.
  newNode->filename = fn;
  newNode->numFound = 1;
  // If the list is empty just put the node in front.
  if (list->front == NULL) {
    list->front = newNode;
    list->back = newNode;
	newNode->next = NULL;
	return 1;
  }
  // Otherwise search for the file and, if not present, add it to the back of the list. 
  else {
	while (curr != NULL) {
		// Found file
		if (strcmp(curr->filename, fn) == 0) {
			curr->numFound++;
			free(newNode->filename);
			free(newNode);
			return 1;
		}
		curr = curr->next;
	}
	// Did not find file
	list->back->next = newNode;
	list->back = newNode;
	newNode->next = NULL;
	return 1;
  }
  return 0;
}

/*
 * output prints out the results of the search, depending on the search mode.
 */
 
void output(SearchResultPtr list, int mode, int maxfind) {
	SNode *curr;
	int first = 0;
	curr = list->front;
	switch (mode) {
		case 0:
			while (curr != NULL) {
				if (curr->next == NULL) {
					printf("%s\n", curr->filename);
				} else {
					printf("%s, ", curr->filename);
				}
				curr = curr->next;
			}
			break;
		case 1:
			while (curr != NULL) {
				if (curr->numFound == maxfind && first == 0) {
					printf("%s", curr->filename);
					first++;
				} else if (curr->numFound == maxfind) {
					printf(", %s", curr->filename);
				}
				curr = curr->next;
			}
			printf("\n");
			break;
		default:
			printf("Error: invalid output mode.\n");
			break;
	}
}
