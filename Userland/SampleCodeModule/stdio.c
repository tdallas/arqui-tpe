#include <stdio.h>

#define BORRA_BUFFER while (getchar() != '\n')
#define BUFFERSIZE 80
#define INT_BUFFER_SIZE 12

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


int printf(const char *str, ...){
    va_list arguments;
    va_start(arguments, str);
    return vprintf(str, arguments);
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
    va_end(arguments);
    return strIndex;
}

int sscanf(const char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    return vsscanf(str, format, args);
}

int scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    char buffer[BUFFERSIZE];
    readLine(buffer);
    return vsscanf(buffer, format, args);
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
                strIndex += stringToInt(str, num);
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
            ++formatIndex;
        }
    }
    va_end(args);
    return n;
}

void readLine(char buff[BUFFERSIZE])
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
            if (bufferIndex <= BUFFERSIZE)
            {
                buff[bufferIndex++] = c;
            }
            putchar(c);
        }
    }
    buff[bufferIndex] = '\0';
    return;
}