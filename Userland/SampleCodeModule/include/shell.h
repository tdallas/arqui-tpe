#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <constantPrints.h>
#include <stdlib.h>
#include <blobsFront.h>
#include <digitalTime.h>

void shell();
void managingCases(char *option);
void help();
void exceptions(int code);
void displayTime();
void blobwars();
void printingMenu();

extern int opCode();
extern int zeroDiv();

#endif