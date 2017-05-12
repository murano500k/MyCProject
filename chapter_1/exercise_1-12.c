#include <stdio.h>

int main()
{
    int c;
    int inword = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (inword)
                putchar('\n');
            inword = 0;
        } else {
            putchar(c);
            inword = 1;
        }
    }
}