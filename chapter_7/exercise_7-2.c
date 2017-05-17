/*

Write a program that will print arbitrary input in a sensible way. As a
minimum, it should print non-graphic characters in octal or hexadecimal
according to local custom, and break long text lines.

*/

#include <stdio.h>
#include <string.h>


int main()
{
    int c;
    int i = 0;

    while ((c = getchar()) != EOF) {

        if (((int)c)>=65 && ((int)c)<=122) {
            printf("[%4c]", c);
        } else
            printf("[0x%x]", c);

        if (i++ == 10) {
            printf("\n");
            i = 0;
        }
    }
}

