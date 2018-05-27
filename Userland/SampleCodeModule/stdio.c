#include <stdio.h>

#define BORRA_BUFFER while (getchar() != '\n')

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

void printf(const char *str, ...)
{
    char num[12];
    va_list arguments;
    va_start(arguments, str);
    int length = strlen(str);
    int state = 0;
    for (int x = 0; x < length; x++)
    {
        if (state == 0)
        {
            if (str[x] != '%')
                putchar(str[x]);
            else
                state = 1;
        }
        else
        {
            switch (str[x])
            {
            case 'd':
            case 'i':
                inToString(va_arg(arguments, int), num);
                int index = 0;
                while (num[index] != 0)
                    putchar(num[index++]);
                state = 0;
                break;
            case 'c':
                putchar((char)(va_arg(arguments, int)));
                state = 0;
                break;
            case 's':
                printf(va_arg(arguments, char *));
                state = 0;
                break;
            default:
                putchar('%');
                putchar(str[x]);
                state = 0;
                break;
            }
        }
    }
    va_end(arguments);
}

int sscanf(char *str, const char *format, ...)
{

    va_list args;
    va_start(args, format);

    int n = 0;
    char *character;
    int *num;

    while (*format != '\0')
    {
        if (*format != '%')
        {
            if ((*format) != (*str))
            {
                return n;
            }
            else
            {
                format++;
                str++;
            }
        }
        else
        {
            switch (*(++format))
            {
            case '%':
                if (*str != '%')
                    return n;
                else
                    str++;
                break;
            case 'd':
            case 'i':
                num = va_arg(args, int *);
                str = readInt(str, num);
                n++;
                break;
            case 'c':
                character = va_arg(args, char *);
                *character = *str++;
                n++;
                break;
            case 's':
                character = va_arg(args, char *);
                while (!isSpace(*str) && *str != '\0')
                {
                    *character = *str;
                    character++;
                    str++;
                }
                n++;
            }
            ++format;
        }
    }
    return n;
}

int scanf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    int n = 0;
    char *str = readLine();
    char *character;
    int *num;

    while (*format != '\0')
    {
        if (*format != '%')
        {
            if ((*format) != (*str))
            {
                return n;
            }
            else
            {
                format++;
                str++;
            }
        }
        else
        {
            switch (*(++format))
            {
            case '%':
                if (*str != '%')
                    return n;
                else
                    str++;
                break;
            case 'd':
            case 'i':
                num = va_arg(args, int *);
                str = readInt(str, num);
                n++;
                break;
            case 'c':
                character = va_arg(args, char *);
                *character = *str++;
                n++;
                break;
            case 's':
                character = va_arg(args, char *);
                while (!isSpace(*str) && *str != '\0')
                {
                    *character = *str;
                    character++;
                    str++;
                }
                n++;
            }
            ++format;
        }
    }

    return n;
}

char *readLine()
{
    int bufferIndex = 0;
    char *buff = malloc(80 + 1);

    int c;

    while ((c = getchar()) != '\n')
    {
        if (c == '\b')
        {
            if (bufferIndex != 0)
            {
                bufferIndex--;
                putchar('\b');
            }
        }
        else if (c != -1)
        {
            if (bufferIndex <= 80)
            {
                buff[bufferIndex++] = c;
            }
            putchar(c);
        }
    }
    buff[bufferIndex] = '\0';
    return buff;
}

//Esta funcion esta bien, ya la probe(No es la de nico, la hice yo), lo que hace es guardar el numero que esta en el string en el puntero num.
char *readInt(char *string, int *num)
{
    *num = 0;
    int sign = 1;
    if( *string == '+' || *string == '-' )
    {
        if( *string == '-' ) sign = -1;
        string++;
    }
    while (isDigit(*string))
    {
        (*num) *= 10;
        (*num) += (int) (*string-'0');
        string++;
    }
    (*num) *= sign;
    return string;
}