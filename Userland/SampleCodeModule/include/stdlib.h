#ifndef STDLIB_H
#define STDLIB_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define RAND_MAX 32767

int rand();
void srand(unsigned int seed);
char toLower(char c);
char toUpper(char c);
int isSpace(char c);
int isDigit(char c);
int isAlpha(char c);
int stringIsAlpha(char *s);
int stringIsNum(char *string);
void inToString(int num, char *ret);

#endif