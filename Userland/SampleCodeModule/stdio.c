#include <stdio.h>

int abs(int a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

int getchar()
{
    return systemCall(1, 0, 0, 0, 0, 0);
}

void putchar(char c)
{
    if (c != 0)
        systemCall(2, (uint64_t)c, 0, 0, 0, 0);
}

void *malloc(long unsigned int size)
{
    if (size == 0)
    {
        return NULL;
    }
    return (void *)systemCall(4, (uint64_t)size, 0, 0, 0, 0);
}

void free(void *pointer)
{
    return;
}

int printf(const char *str, ...)
{
    int result;
    va_list arguments;
    va_start(arguments, str);
    result = vprintf(str, arguments);
    va_end(arguments);
    return result;
}

int vprintf(const char *str, va_list arguments)
{
    char num[INT_BUFFER_SIZE];
    int strIndex = 0;
    while (str[strIndex] != '\0')
    {
        if (str[strIndex] != '%')
        {
            putchar(str[strIndex]);
        }
        else
        {
            switch (str[++strIndex])
            {
            case 'd':
            case 'i':
                inToString(va_arg(arguments, int), num);
                int index = 0;
                while (num[index] != 0)
                    putchar(num[index++]);
                break;
            case 'c':
                putchar((char)(va_arg(arguments, int)));
                break;
            case 's':
                printf(va_arg(arguments, char *));
                break;
            default:
                putchar('%');
                putchar(str[strIndex]);
                break;
            }
        }
        strIndex++;
    }
    return strIndex;
}

int sscanf(const char *str, const char *format, ...)
{
    int result;
    va_list args;
    va_start(args, format);
    result = vsscanf(str, format, args);
    va_end(args);
    return result;
}

int vsscanf(const char *str, const char *format, va_list args)
{

    int strIndex = 0;
    int formatIndex = 0;
    int n = 0;
    char *character;
    int *num;

    while (format[formatIndex] != '\0')
    {
        if (format[formatIndex] != '%')
        {
            if (format[formatIndex] != str[strIndex])
            {
                return n;
            }
            else
            {
                formatIndex++;
                strIndex++;
            }
        }
        else
        {
            switch (format[++formatIndex])
            {
            case '%':
                if (str[strIndex] != '%')
                    return n;
                else
                    strIndex++;
                break;
            case 'd':
            case 'i':
                num = va_arg(args, int *);
                strIndex += stringToInt(str + strIndex, num);
                n++;
                break;
            case 'c':
                character = va_arg(args, char *);
                *character = str[strIndex++];
                n++;
                break;
            case 's':
                character = va_arg(args, char *);
                while (!isSpace(str[strIndex]) && str[strIndex] != '\0')
                {
                    *character = str[strIndex];
                    character++;
                    strIndex++;
                }
                n++;
            }
            formatIndex++;
        }
    }
    return n;
}

int readLine(char buffer[BUFFER_SIZE])
{
    int bufferIndex = 0;
    int c;

    while ((c = getchar()) != '\n')
    {
        if (c == '\b')
        {
            if (bufferIndex > 0)
            {
                bufferIndex--;
                putchar('\b');
            }
        }
        else if (c != EOF)
        {
            if (bufferIndex <= BUFFER_SIZE)
            {
                buffer[bufferIndex++] = c;
            }
            putchar(c);
        }
    }
    putchar('\n');
    buffer[bufferIndex++] = '\n';
    buffer[bufferIndex++] = '\0';
    return bufferIndex;
}

static int bufferFlag = 0;

int scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    char buffer[BUFFER_SIZE];
    int bufferLength = readLine(buffer);
    int bufferIndex = 0;
    int formatIndex = 0;
    int result = 0;
    int flag = 0;
    int auxIndex;

    char *auxChar;
    int *auxNum;

    while (format[formatIndex] != '\0' && !flag && bufferIndex < bufferLength)
    {
        if (format[formatIndex] != '%')
        {
            if (format[formatIndex] != buffer[bufferIndex])
            {
                flag = 1;
            }
            else
            {
                formatIndex++;
                bufferIndex++;
            }
        }
        else
        {
            formatIndex++;
            switch (format[formatIndex])
            {
            default:
                if (buffer[bufferIndex] != '%')
                {
                    flag = 1;
                }
                else
                {
                    bufferIndex++;
                }
                break;
            case 'd':
            case 'i':
                auxNum = va_arg(args, int *);
                auxIndex = bufferIndex;
                bufferIndex += stringToInt(buffer + bufferIndex, auxNum);
                if(bufferIndex > auxIndex){
                    result++;
                }
                formatIndex++;
                break;
            case 'c':
                auxChar = va_arg(args, char *);
                if(isAlpha(buffer[bufferIndex])){
                    *auxChar = buffer[bufferIndex++];
                    result++;
                }
                formatIndex++;
                break;
            case 's':
                auxChar = va_arg(args, char *);
                auxIndex = bufferIndex;
                while (!isSpace(buffer[bufferIndex]) && buffer[bufferIndex] != '\0')
                {
                    *auxChar = buffer[bufferIndex];
                    auxChar++;
                    bufferIndex++;
                }
                if(bufferIndex > auxIndex){
                    result++;
                }
                formatIndex++;
                break;
            }
        }
    }

    putStringKeyboardBuffer(buffer+bufferIndex); //Guarda en buffer lo no utilizado, esto es para que el scanf funcione como el de c

    if(bufferFlag && bufferIndex == 0){ //En la anterior salio primero y en la actual tambien entonces borro el buffer
        BORRA_BUFFER
        bufferFlag = 0;      // Es variable static
    }
    else{
        bufferFlag = 0;
    }

    if(bufferIndex == 0){  //Salio en el primero
        bufferFlag = 1;
    }

    va_end(args);
    return result;
}

void putStringKeyboardBuffer(char *s){
    systemCall(6, (uint64_t)s, 0, 0, 0, 0);
}


void clearWorkSpace()
{
    systemCall(5, 0, 0, 0, 0, 0);
}