#ifndef TOKENIZER_H
#define TOKENIZER_H
/*
 * tokenizer.h
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Input type. Used to parse through the file's content.
 * Holds a string buffer and the length of the current string being stored,
 * as well as how much is being used
 */

struct input {
	FILE *fp;	//file ptr
	int length;	//length of input
	int used;	//bytes given to user
	char buffer[2048];	//buffer
};
typedef struct input Input;

/*
 * isAlphaNum checks to see if the current character is alphanumeric.
 * If it succeeds it returns 1, otherwise it returns 0.
 */

int isAlphaNum(char c);

/*
 * resetImput initaliazes/reinitializes the input struct.
 */
 
void resetInput(Input *iPtr, FILE *fp);

/*
 * readInput reads and return a single char from the input struct.
 * It also returns the char as a lowercase letter if it is uppercase.
 * If it succeeds it returns a character, otherwise it returns -1.
 */
 
int readInput(Input *iPtr);

/*
 * IDestroy destroys a Input object.  Frees all dynamically
 * allocated memory that is part of the object.
 */

void IDestroy(Input *iPtr);

/*
 * IGetNextToken returns the next token from the buffer held in the Input struct. On success it 
 * returns a null-terminated character string, otherwise it returns NULL.
 */

char *IGetNextToken(Input *iPtr);

#endif
