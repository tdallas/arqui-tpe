#include <stdio.h>

#define BORRA_BUFFER while (getchar() != '\n')
#define BUFFERSIZE 80

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

int sscanf(char *line, char *fmt, ...)
{

    va_list args;
    va_start(args, fmt);

    int n = 0;
    char *character;
    int *num;

    while (*fmt != '\0')
    {
        if (*fmt != '%')
        {
            if ((*fmt) != (*line))
            {
                return n;
            }
            else
            {
                fmt++;
                line++;
            }
        }
        else
        {
            switch (*(++fmt))
            {
            case '%':
                if (*line != '%')
                    return n;
                else
                    line++;
                break;
            case 'd':
            case 'i':
                num = va_arg(args, int *);
                line += stringToInt(line, num);
                n++;
                break;
            case 'c':
                character = va_arg(args, char *);
                *character = *line++;
                n++;
                break;
            case 's':
                character = va_arg(args, char *);
                while (!isSpace(*line) && *line != '\0')
                {
                    *character = *line;
                    character++;
                    line++;
                }
                n++;
            }
            ++fmt;
        }
    }
    return n;
}

int scanf(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int n = 0;
    char str[BUFFERSIZE];
    readLine(str);
    char *line = str;
    char *character;
    int *num;

    while (*fmt != '\0')
    {
        if (*fmt != '%')
        {
            if ((*fmt) != (*line))
            {
                return n;
            }
            else
            {
                fmt++;
                line++;
            }
        }
        else
        {
            switch (*(++fmt))
            {
            case '%':
                if (*line != '%')
                    return n;
                else
                    line++;
                break;
            case 'd':
            case 'i':
                num = va_arg(args, int *);
                line += stringToInt(line, num);
                n++;
                break;
            case 'c':
                character = va_arg(args, char *);
                *character = *line++;
                n++;
                break;
            case 's':
                character = va_arg(args, char *);
                while (!isSpace(*line) && *line != '\0')
                {
                    *character = *line;
                    character++;
                    line++;
                }
                n++;
            }
            ++fmt;
        }
    }

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
            if (bufferIndex != 0)
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

/*int sscanf(char *line, char* fmt, ...) 
{ 
    char *traverse;
    unsigned int i; 

    char * str; 
    int * int_ptr;

    int count = 0;

    va_list arg; 
    va_start(arg, fmt); 

    char * buf = line;
    char aux[BUFFERSIZE];

    for(traverse = fmt; *traverse != '\0' && *buf != '\0'; traverse++) 
    { 
        while( *traverse != '%'){ //Avanzo hasta el %
            //Si no matchean
            if(*traverse != *buf){ //Dejo de leer, ya no cumple el formato
                  va_end(arg);
                return count; 
            }

            buf++;
            traverse++; 
        } 

        if(*traverse == 0){
            va_end(arg); 
            return count; //Termine
        }

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) { 
            case 'i' :
            case 'd' :
                        int_ptr = va_arg(arg,int *); //Leo puntero

                        if(*buf != '-' && !isDigit(*buf)){
                            va_end(arg);
                            return count;
                        }
                      

                        aux[0] = *(buf++); //Copio el primero (digito o '-')
                        for(i=1; isDigit(*buf) && i < BUFFERSIZE - 1; buf++, i++){ 
                            //Copio el resto de los digitos
                            aux[i] = *buf;
                        }
                        aux[i] = '\0';
                        stringToInt(aux, int_ptr);
                        count++;

                        break; 

            case 's' : str = va_arg(arg, char *);       //Fetch string
                      strncpy(str, buf, strlen(buf)); //Copio hasta el final en s
                      count++;
                      va_end(arg); 
                      return count;
                      break; 

        }   
    } 

    //Cerrando la lista variable
    va_end(arg); 
    return count;
} 

//Scanf con %d, %s
int scanf(char* fmt, ...) 
{ 
    char *traverse;
    unsigned int i; 

    char * str; 
    int * int_ptr;

    int count = 0;

    va_list arg; 
    va_start(arg, fmt); 

    char line[BUFFERSIZE];
    char * buf = line;
    char aux[BUFFERSIZE];

    readLine(line);

    for(traverse = fmt; *traverse != '\0' && *buf != '\0'; traverse++) 
    { 
        while( *traverse != '%'){ //Avanzo hasta el %
            //Si no matchean
            if(*traverse != *buf){ //Dejo de leer, ya no cumple el formato
                  va_end(arg);
                return count; 
            }

            buf++;
            traverse++; 
        } 

        if(*traverse == 0){
            va_end(arg); 
            return count; //Termine
        }

        traverse++; 

        //Module 2: Fetching and executing arguments
        switch(*traverse) { 
            case 'i' :
            case 'd' :
                        int_ptr = va_arg(arg,int *); //Leo puntero

                        if(*buf != '-' && !isDigit(*buf)){
                            va_end(arg);
                            return count;
                        }
                      

                        aux[0] = *(buf++); //Copio el primero (digito o '-')
                        for(i=1; isDigit(*buf) && i < BUFFERSIZE - 1; buf++, i++){ 
                            //Copio el resto de los digitos
                            aux[i] = *buf;
                        }
                        aux[i] = '\0';
                        stringToInt(aux, int_ptr);
                        count++;

                        break; 

            case 's' : str = va_arg(arg, char *);       //Fetch string
                      strncpy(str, buf, strlen(buf)); //Copio hasta el final en s
                      count++;
                      va_end(arg); 
                      return count;
                      break; 

        }   
    } 

    //Cerrando la lista variable
    va_end(arg); 
    return count;
}*/