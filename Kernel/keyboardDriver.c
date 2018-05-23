#include <keyboardDriver.h>

const char keyMap[128] =
    {
        0, 27, '1', '2', '3', '4', '5', '6', '7', '8',                  /* 9 */
        '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',             /* 19 */
        't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,                /* 29   - Control */
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',               /* 39 */
        '\'', '`', 0, /*leftshift*/ '\\', 'z', 'x', 'c', 'v', 'b', 'n', /* 49 */
        'm', ',', '.', '/', 0, /*rightshift*/ '*',                      /*55*/
        0,                                                              /* Alt -56*/
        ' ',                                                            /* Space bar -57*/
        0,                                                              /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               /* < ... F10 */
        0,                                                              /* Num lock -68*/
        0,                                                              /* Scroll Lock -69*/
        0,                                                              /* Home key -70*/
        15,                                                             /* Up Arrow -71*/
        0,                                                              /* Page Up -72*/
        '-',                                                            /* minus -73*/
        13,                                                             /* Left Arrow */
        0,
        12, /* Right Arrow */
        '+',
        0,  /* 79 - End key*/
        14, /* Down Arrow */
        14, /* Page Down */
        0,  /* Insert Key */
        0,  /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

const char shiftKeyMap[128] =
    {
        0, 27, '!', '@', '#', '$', '%', '^', '&', '*',                  /* 9 */
        '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',             /* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,                /* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',               /* 39 */
        '\'', '`', 0, /*leftshift*/ '\\', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
        'M', '<', '>', '?', 0, /*rightshift*/ '*',                      /*55*/
        0,                                                              /* Alt -56*/
        ' ',                                                            /* Space bar -57*/
        0,                                                              /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,               /* < ... F10 */
        0,                                                              /* Num lock -68*/
        0,                                                              /* Scroll Lock -69*/
        0,                                                              /* Home key -70*/
        15,                                                             /* Up Arrow -71*/
        0,                                                              /* Page Up -72*/
        '-',                                                            /* minus -73*/
        13,                                                             /* Left Arrow */
        0,
        12, /* Right Arrow */
        '+',
        0,  /* 79 - End key*/
        14, /* Down Arrow */
        14, /* Page Down */
        0,  /* Insert Key */
        0,  /* Delete Key */
        0, 0, 0,
        0, /* F11 Key */
        0, /* F12 Key */
        0, /* All other keys are undefined */
};

/* Handles the keyboard interrupt */

static char circularBuffer[BUFFERSIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elements = 0;
static int shiftKey = 0;
static int altKey = 0;
static int controlKey = 0;
static int capsKey = 0;
static int print = 1;

void keyboard_handler()
{
  unsigned char keycode;
  keycode = get_key();
  unsigned char scancode;
  /* Read from the keyboard's data buffer */
  scancode = get_key();

  /* If the top bit of the byte we read from the keyboard is
    *  set, that means that a key has just been released */
  if (scancode & 0x80)
  {

    if (scancode == 182 || scancode == 170)
    {
      shiftKey = 0;
    }
    if (scancode == 157)
    {
      controlKey = 0;
    }
    if (scancode == 184)
    {
      altKey = 0;
    }
  }
  else
  {
    /* Here, a key was just pressed. Please note that if you
          *  hold a key down, you will get repeated key press
          *  interrupts. */

    /* Just to show you how this works, we simply translate
          *  the keyboard scancode into an ASCII value, and then
          *  display it to the screen. You can get creative and
          *  use some flags to see if a shift is pressed and use a
          *  different layout, or you can add another 128 entries
          *  to the above layout to correspond to 'shift' being
          *  held. If shift is held using the larger lookup table,
          *  you would add 128 to the scancode when you look for it */
    if (scancode == 58)
    { //CAPSLOCK
      capsKey = !capsKey;
    }
    if (scancode == 54 || scancode == 42)
    { //shift
      shiftKey = 1;
      print = 0;
    }
    if (scancode == 29)
    { //control
      controlKey = 1;
      print = 0;
    }
    if (scancode == 56)
    { //alt
      altKey = 1;
      print = 0;
    }
    char c = keyMap[scancode];
    if ('a' <= c && c <= 'z' && ((shiftKey == 1 && capsKey == 0) || (shiftKey == 0 && capsKey == 1)))
    {
      c -= ('a' - 'A');
    }
    else
    {
      if (shiftKey == 1)
      {
        c = shiftKeyMap[scancode];
      }
    }
    if (print == 1)
    {
      putChar(c);
    }
    print = 1;
  }
}

void reset(char *string, int size)
{
  for (int i = 0; i < size; i++)
  {
    *(string + i) = 0;
  }
}
int isEmpty()
{
  return elements == 0;
}
void getChar(char *ch)
{
  if (isEmpty())
  {
    *ch = EOF;
    return;
  }
  *ch = circularBuffer[readIndex];
  readIndex = (readIndex + 1) % BUFFERSIZE;
  elements--;
}

void putChar(char c)
{
  circularBuffer[writeIndex] = c;
  writeIndex = (writeIndex + 1) % BUFFERSIZE;
  if (elements < BUFFERSIZE)
  {
    elements++;
  }
  else
  {
    readIndex = (readIndex + 1) % BUFFERSIZE;
  }
}