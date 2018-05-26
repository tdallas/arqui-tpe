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
        0, 27, '!', '@', '#', '$', '%', '^', '&', '*',                 /* 9 */
        '(', ')', '_', '+', '\b', '\t', 'Q', 'W', 'E', 'R',            /* 19 */
        'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 0,               /* 29   - Control */
        'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',              /* 39 */
        '\"', '~', 0, /*leftshift*/ '|', 'Z', 'X', 'C', 'V', 'B', 'N', /* 49 */
        'M', '<', '>', '?', 0, /*rightshift*/ '*',                     /*55*/
        0,                                                             /* Alt -56*/
        ' ',                                                           /* Space bar -57*/
        0,                                                             /* Caps lock -58*/
        /*- F1 key ... > */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,              /* < ... F10 */
        0,                                                             /* Num lock -68*/
        0,                                                             /* Scroll Lock -69*/
        0,                                                             /* Home key -70*/
        15,                                                            /* Up Arrow -71*/
        0,                                                             /* Page Up -72*/
        '-',                                                           /* minus -73*/
        13,                                                            /* Left Arrow */
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

static char buffer[BUFFERSIZE] = {0};
static int readIndex = 0;
static int writeIndex = 0;
static int elements = 0;
static int shiftKey = 0;
static int altKey = 0;
static int controlKey = 0;
static int capsKey = 0;
static int printFlag = 1;

void keyboard_handler()
{
  printFlag = 1;
  unsigned char keyCode;
  keyCode = get_key();

  if (keyCode & 0x80)
  {
    if (keyCode == 182 || keyCode == 170)
    {
      shiftKey = 0;
    }
    else if (keyCode == 157)
    {
      controlKey = 0;
    }
    else if (keyCode == 184)
    {
      altKey = 0;
    }
  }
  else
  {
    if (keyCode == 58)
    {
      capsKey = !capsKey;
      printFlag = 0;
    }
    else if (keyCode == 54 || keyCode == 42)
    {
      shiftKey = 1;
      printFlag = 0;
    }
    else if (keyCode == 29)
    {
      controlKey = 1;
      printFlag = 0;
    }
    else if (keyCode == 56)
    {
      altKey = 1;
      printFlag = 0;
    }

    if (printFlag)
    {
      char c = keyMap[keyCode];
      if (shiftKey)
      {
        if (!ISALPHA(c) || !capsKey)
        {
          c = shiftKeyMap[keyCode];
        }
      }
      else
      {
        if (ISALPHA(c) && capsKey)
        {
          c = shiftKeyMap[keyCode];
        }
      }
      buffer[writeIndex] = c;
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
  }
}

int getChar()
{
  if (elements == 0)
  {
    return EOF;
  }
  int c;
  c = buffer[readIndex];
  readIndex = (readIndex + 1) % BUFFERSIZE;
  elements--;
  return c;
}