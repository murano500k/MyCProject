#include <stdio.h>

void my_strcat(char *s, char *t);
void my_strcat(char *s, char *t)
{
    while (*s) s++;
    while ((*s++ = *t++));
}

int main()
{
    char a[] = "Hello\0                        ";
    char b[] = ", world!";
    printf("strcat(\"%s\", \"%s\") = ", a, b);
    my_strcat(a, b);
    printf("\"%s\"", a);
}
