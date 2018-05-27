#include <string.h>

long unsigned int strlen(const char *str)
{
    int count = 0;
    while (*str != '\0')
    {
        count++;
        str++;
    }
    return count;
}

int lowstrcmp(const char *s1, const char *s2)
{
    int i;
    char c1, c2;
    for (i = 0; (c1 = toLower(s1[i])) == (c2 = toLower(s2[i])); i++)
        if (s1[i] == '\0')
            return 0;
    return c1 - c2;
}

int strcmp(const char *s1, const char *s2)
{
    int i;

    for (i = 0; s1[i] == s2[i]; i++)
        if (s1[i] == '\0')
            return 0;
    return s1[i] - s2[i];
}

int strncmp(const char *s1, const char *s2, long unsigned int n){
    int i;

    for (i = 0; s1[i] == s2[i] && i<n; i++)
        if (s1[i] == '\0')
            return 0;
    return s1[i] - s2[i];
}

const char *strchr(const char *s, int c)
{
    if (s == NULL)
    {
        return NULL;
    }
    if ((c > 255) || (c < 0))
    {
        return NULL;
    }
    int s_len;
    int i;
    s_len = strlen(s);
    for (i = 0; i < s_len; i++)
    {
        if ((char)c == s[i])
        {
            return (const char *)&s[i];
        }
    }
    return NULL;
}

char *strncpy(char *destination, const char *source, long unsigned int n){
    char *aux = destination;
    int i = 0;
    while(i < n && *source != '\0'){
        *destination = *source;
        destination++;
        source++;
        i++;
    }
    *destination = '\0';
    return aux;
}
char *strcpy(char *destination, const char *source){
    char *aux = destination;
    while(*source != '\0'){
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
    return aux;
}