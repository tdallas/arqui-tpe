#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define BUFFER_SIZE 80
#define EOF 0

extern int getKeyCode();
int getChar();
void keyboard_handler();
void putCharBuffer(int c);
void putStringBuffer(char *s);

#endif