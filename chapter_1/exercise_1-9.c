#include   <stdio.h>

int main()
{
    int c;

    int prevspace = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ' || !prevspace) {
            putchar(c);
            prevspace = 0;
        }
        if (c == ' ')
            prevspace = 1;
    }
}