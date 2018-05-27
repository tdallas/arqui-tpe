#ifndef STDLIB_H
#define STDLIB_H

#define RAND_MAX 32767

int rand();
void srand(unsigned int seed);
int isDigit(char c);
int isAlpha(char c);
int stringIsAlpha(char *s);
int stringisNum(char *string);
void intostr(int num, char *ret);

#endif