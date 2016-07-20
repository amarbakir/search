#include "sorted-list.h"
#include "sorted-arraymain.h"
#include "searchresult.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int binarySearch(Elem *array, char *key, int low, int high) {
    if (high < low) {
        return -1;
	}
	int mid;
    mid = low + ((high - low) / 2);
    if (strcmp(array[mid].token, key) == 0) {
		return mid;
	} else if (strcmp(array[mid].token, key) < 0) {
		return binarySearch(array, key, (mid + 1), high);
	} else if (strcmp(array[mid].token, key) > 0) {
		return binarySearch(array, key, low, (mid - 1));
	}
	return -1;
}

int main(int argc, char **argv) {
	char input[100];
	char *token;
	int flag = 0;
	if(argc != 2){
		printf("Error: invalid number of arguments\n");
		return 1;
	}
	struct stat statbuf;
	stat(argv[1], &statbuf);
	if(!S_ISREG(statbuf.st_mode)) {
		if(errno != ENOENT) {
			printf("Error: index file is not a text file.\n");
			return 1;
		} else {
			printf("Error: indexer file does not exist.\n");
			return 1;
		}
	}
	if(strstr(argv[1], ".txt") == NULL) {
		printf("Error: output file not a text file.\n");
		return 1;
	}
	MSortedArrayPtr array = readFile(argv[1]);
	printf("What would you like to do?\n");
	printf("'sa <term> ... <term>' search for files that contain all terms\n");
	printf("'so <term> ... <term>' search for files that contain any of the terms\n");
	printf("'q' quit\n");
	fgets(input, 100, stdin);
	while (input[0] != 'q') {
		int mode = 0;
		int counter = 0;
		token = strtok(input, "\n\r ");
		if (token == NULL) {
			printf("Error: No input\n");
			flag = 0;
			printf("What would you like to do?\n");
			printf("'sa <term> ... <term>' search for files that contain all terms\n");
			printf("'so <term> ... <term>' search for files that contain any of the terms\n");
			printf("'q' quit\n");
			fgets(input, 100, stdin);
			continue;
		}
		if (strcmp(token, "so") == 0) {
			flag = 1;
			mode = 0;
		} else if (strcmp(token, "sa") == 0) {
			mode = 1;
			flag = 1;
		}
		if (mode == 1) {
			printf("mode is 'search and'\n");
		} else if (mode == 0) {
			printf("mode is 'search or'\n");
		}
		SearchResultPtr sr = SRCreate();
		token = strtok(NULL, "\n\r ");
		while (token != NULL) {
			Elem *item;
			int index;
			index = binarySearch(array->ElemArray, token, 0, (array->numElem) - 1);
			if (index != -1) {
				item = &(array->ElemArray[index]);
			} else {
				token = strtok(NULL, "\n\r ");
				continue; 
			}
			if (item != NULL) {
				counter++;
				Node *curr;
				curr = item->sl->front;
				while (curr != NULL) {
					SRInsert(sr, curr->filename);
					curr = curr->next;
				}
			}
			token = strtok(NULL, "\n\r ");
		}
		output(sr, mode, counter);
		SRDestroy(sr);
		if (flag != 1) {
			printf("Error: invalid input format\n\n");
		}
		flag = 0;
		printf("What would you like to do?\n");
		printf("'sa <term> ... <term>' search for files that contain all terms\n");
		printf("'so <term> ... <term>' search for files that contain any of the terms\n");
		printf("'q' quit\n");
		fgets(input, 100, stdin);
	}
	MSADestroy(array);
	return 0;
}
