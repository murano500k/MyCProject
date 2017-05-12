#include <stdio.h>

int main()
{
    int lim = 5;
    int c;

    printf("BEFORE:\n");
    for (int i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
        putchar(c);

    printf("\n\n\nAFTER:\n");
    int i = 0;
    while (1) {
        if (i == lim - 1) break;
        c = getchar();
        if (c == '\n') break;
        if (c == EOF) break;
        putchar(c);
        ++i;
    }
}