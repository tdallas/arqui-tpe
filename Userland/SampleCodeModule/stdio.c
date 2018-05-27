#include <stdio.h>

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
    if(size == 0){
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
    char *num = malloc(12);
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