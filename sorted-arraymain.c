#include "sorted-arraymain.h"
#include <string.h>
#include <stdio.h>

/*
 * MSLCreate creates a new, empty main sorted list.  If the function succeeds, 
 * it returns a (non-NULL) MSortedList object, otherwise, it returns NULL.
 */

MSortedArrayPtr MSACreate() {
  // Creating and mallocing the sl to be returned via the pointer sl.
  MSortedArrayPtr sa;
  sa = (struct MainSortedArray *)malloc(sizeof(struct MainSortedArray));
  // If malloc fails print an error statement and return NULL.
  if (sa == NULL) {
    //printf("Error: Out of memory.\n");
    return NULL;
  }
  sa->ElemArray = (Elem *)malloc(50 * sizeof(Elem));
  sa->arraySize = 50;
  sa->numElem = 0;
  return sa;
}

/*
 * MSLDestroy destroys a list, freeing all dynamically allocated memory.
 */
 
void MSADestroy(MSortedArrayPtr array) {
	int i;
  for (i = 0; i < array->numElem; i++) {
	  free(array->ElemArray[i].token);
	  SLDestroy(array->ElemArray[i].sl);
  }
  // Freeing the array after we destroy all the sub-lists.
  free(array);
}

/*
 * isStart checks to see if the current line is the start of a list, and adds an entry 
 * into the array if it is. If it succeeds it returns 1, otherwise it returns 0.
 */

int isStart(char *c, MSortedArrayPtr array) {
  char *token;
  char *tk;
  token = strtok(c, "\n\r ");
  if (strcmp(token, "<list>") == 0){
	  token = strtok(NULL, "\n\r ");
	  tk = (char *)malloc(strlen(token) + 1);
	  if (tk == NULL) {
		  printf("Error: out of memory.");
		  return 0;
	  }
	  strcpy(tk, token);
	  tk[strlen(token)] = '\0';
	  if (array->numElem == array->arraySize) {
		  array->ElemArray = realloc(array->ElemArray, 2 * array->arraySize);
		  array->arraySize = 2 * array->arraySize;
	  }
	  array->ElemArray[array->numElem].token = tk;
	  array->ElemArray[array->numElem].sl = SLCreate();
	  array->numElem++;
	  if (array->ElemArray[(array->numElem) - 1].sl == NULL) {
		//printf("Error: Out of memory.\n");
		return 0;
	  }
  	  return 1;
  }
  return 0;
}

/*
 * isEnd checks to see if the current line is the end.
 * If it succeeds it returns 1, otherwise it returns 0.
 */

int isEnd(char *c) {
  if (strstr(c, "</list>") != NULL){
	  return 1;
  }
  return 0;
}

/*
 * readLine reads in the current line (and tests to make sure it is a valid line) to an 
 * element in an array of Elements. If it succeeds it returns 1, otherwise it returns 0.
 */

int readLine(char *c, SortedListPtr list) {
  char *token;
  long freq;
  if (strstr(c, "<list>") != NULL || strstr(c, "</list>") != NULL){
	  return 0;
  }
  token = strtok(c, "\n\r ");
  while (token != NULL) {
	  char *temp;
	  temp = strtok(NULL, "\n\r ");
	  freq = strtol(temp, NULL, 10);
	  if (SLInsert(list, token, freq) == 0) {
		  return 0;
	  }
	  token = strtok(NULL, "\n\r ");
  }
  return 1;
}

/*
 * readFile reads and creates a sorted array based on the filename of an indexer passed
 * to the function as fn. If it succeeds it returns the array, otherwise it returns NULL.
 */
 
MSortedArrayPtr readFile(char *fn) {
	int counter = 0;
	FILE *fp;
	char curr[1000];
	int mode = 0;
	MSortedArrayPtr array = MSACreate();
	fp = fopen(fn, "r");
	while (fgets(curr, 1000, fp) != NULL) {
		counter++;
		switch (mode) {
			case 0:
				if (isStart(curr, array) == 1) {
					mode = 1;
				}
				break;
			case 1:
				if (isEnd(curr) == 1) {
					mode = 0;
				} else {
					if (readLine(curr, array->ElemArray[(array->numElem) - 1].sl) == 0) {
						return NULL;
					}
				}
				break;
			default:
				return NULL;
				break;
		}
	}
	return array;
}
