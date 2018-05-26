#ifndef KEYBOARD_DRIVER_H
#define KEYBOARD_DRIVER_H

#define BUFFER_SIZE 80
#define EOF 0
#define IS_ALPHA(C) ((C >= 'a' && C <= 'z') ? 1 : 0)

extern int getKeyCode();
int getChar();
void keyboard_handler();

#endif