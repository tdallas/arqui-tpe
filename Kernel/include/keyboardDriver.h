#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define BUFFERSIZE 80
#define EOF 0
#define ISALPHA(C) ((C >= 'a' && C <= 'z') ? 1 : 0)

extern int get_key();
int getChar();
void keyboard_handler();

#endif