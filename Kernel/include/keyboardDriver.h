#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define BUFFERSIZE 64
#define EOF -1

extern int key_pressed();
extern int get_key();
void getChar(char * ch);
void readAllBuffer(char *);
int isEmpty();
void putChar(char c);
void keyboard_handler();

#endif