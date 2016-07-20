#include "sorted-list.h"
#include "sorted-listmain.h"
#include "tokenizer.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int indexFile(MSortedListPtr mlist, FILE *fp, char *filepath) {
	Input *in;
	char *token;
	MNode *search;
	in = (Input *)malloc(sizeof(Input));
	if (in == NULL) {
		printf("Error: not enough memory.\n");
		return 0;
	}
	resetInput(in, fp);
	while((token = IGetNextToken(in)) != NULL) {
		search = MSLInsert(mlist, token);
		if(search == NULL) {
			printf("Search for token failed.\n");
			exit(EXIT_FAILURE);
		}
		if(SLInsert(search->sl, filepath) == 0) {
			printf("Error: file indexing failed.\n");
			free(in);
			return 0;
		}
		free(token);
	}
	free(in);
	return 1;
}

int indexDir(MSortedListPtr mlist, DIR *dp, char *currpath) {
	struct dirent *entry;
	FILE *fp;
	while ((entry = readdir(dp)) != NULL) {
		char *path;
		path = (char *)malloc((strlen(currpath) + 1 + strlen(entry->d_name) + 1) * sizeof(char));
		int newfplength;
		strcpy(path, currpath);
		strcat(path, "/");
		strcat(path, entry->d_name);
		newfplength = strlen(path);
		if (newfplength >= PATH_MAX) {
			printf("Error: path length is too long.\n");
			free(path);
			exit(EXIT_FAILURE);
		}
		struct stat statbuf;
		stat(path, &statbuf);
		if(S_ISDIR(statbuf.st_mode)) {
			if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				printf("Dir not a proper dir. Skipping %s\n", path);
				continue;
			}
			DIR *dirptr;
			if ((dirptr = opendir(path)) != NULL) {
				indexDir(mlist, dirptr, path);
				closedir(dirptr);
			}
			else {
				printf("Error: directory %s could not be opened.\n", path);
				exit(EXIT_FAILURE);
			}
		}
		else if(S_ISREG(statbuf.st_mode)) {
			if(strstr(entry->d_name, ".txt") == NULL) {
				printf("File not a text file. Skipping file %s\n", path);
				continue;
			}
			if(strstr(entry->d_name, "~") != NULL) {
				printf("File is a temporary file. Skipping file %s\n", path);
				continue;
			}
			if ((fp = fopen(path, "r")) != NULL) {
				indexFile(mlist, fp, path);
				fclose(fp);
			}
			else {
				printf("Error: file %s could not be opened.\n", path);
				exit(EXIT_FAILURE);
			}
		}
	free(path);	
	}
	return 1;
}

void output(MSortedListPtr mlist, char *outputname) {
	FILE *fp;
	fp = fopen(outputname, "w");
	MNode *mainptr;
	Node *ptr;
	int counter = 0;
	mainptr = mlist->front;
	while(mainptr != NULL) {
		fprintf(fp, "<list> %s\n", mainptr->token);
		ptr = mainptr->sl->front;
		counter = 0;
		while(ptr != NULL) {
			counter++;
			if(counter >= 5) {
				fprintf(fp, "%s %d\n", ptr->filename, ptr->freq);
				counter = 0;
			}
			else {
				fprintf(fp, "%s %d ", ptr->filename, ptr->freq);
			}
			ptr = ptr->next;
		}
		if(counter != 0) {
			fprintf(fp, "\n");
		}
		fprintf(fp, "</list>\n");
		mainptr = mainptr->next;
	}
	fclose(fp);
}

int main(int argc, char **argv) {
	if(argc != 3){
		printf("Error: invalid number of arguments\n");
		return 1;
	}
	struct stat statbuf;
	stat(argv[1], &statbuf);
	if(!S_ISREG(statbuf.st_mode)) {
		if(errno != ENOENT) {
			printf("Error: output file is not a text file.\n");
			return 1;
		}
	}
	if(strstr(argv[1], ".txt") == NULL) {
		printf("Error: output file not a text file.\n");
		return 1;
	}
	char *path;
	path = (char *)malloc((strlen(argv[2]) + 1) * sizeof(char));
	strcpy(path, argv[2]);
	if (strlen(path) >= PATH_MAX) {
		printf("Error: path length is too long.\n");
		free(path);
		exit(EXIT_FAILURE);
	}
	stat(argv[2], &statbuf);
	if(S_ISREG(statbuf.st_mode)) {
		if(strstr(argv[2], ".txt") == NULL) {
			printf("Error: Input file not a text file.\n");
			return 1;
		} else {
			if(strcmp(argv[1], argv[2]) == 0) {
				printf("Input and output file are the same.\nAre you sure you want to continue and overwrite the input file (y/n)(default: n)?");
				char i;
				scanf(" %c", &i);
				switch (i) {
					case 'y':
						break;
					case 'n':
						printf("Error: input file and output file are the same.\n");
						return 1;
						break;
					default:
						printf("Error: input file and output file are the same.\n");
						return 1;
				}
			}
			FILE *fp;
			fp = fopen(argv[2], "r");
			MSortedListPtr mlist;
			mlist = MSLCreate();
			indexFile(mlist, fp, path);
			fclose(fp);
			output(mlist, argv[1]);
			MSLDestroy(mlist);
		}
	} else if(S_ISDIR(statbuf.st_mode)) {
		DIR *dir;
		dir = opendir(path);
		MSortedListPtr mlist;
		mlist = MSLCreate();
		indexDir(mlist, dir, path);
		closedir(dir);
		output(mlist, argv[1]);
		MSLDestroy(mlist);
	}
	free(path);
	return 0;
}
