#ifndef TIME_H
#define TIME_H

#include <stdio.h>

long int time(void *value);
void getAllTimes(int times[7]);
int getTimeUTC();
void setTimeUTC(int newUTC);
void printTime();

#endif