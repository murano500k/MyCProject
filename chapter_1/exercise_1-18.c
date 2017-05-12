#include <stdio.h>
#define MAX_SPACE_RUN  80

int main()
{
    char whitespace[MAX_SPACE_RUN + 1];
    int ix = 0;
    int blank_line = 1;

    int c;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t') {
            if (ix == MAX_SPACE_RUN - 2) {
                printf("%s", whitespace);
                for (int i = 0; i < MAX_SPACE_RUN + 1; i++)
                    whitespace[i] = 0;
                ix = 0;
            }
            whitespace[ix++] = (char) c;
        } else if (c == '\n') {
            for (int i = 0; i < MAX_SPACE_RUN + 1; i++)
                whitespace[i] = 0;
            ix = 0;
            if (!blank_line) {
                putchar(c);
            }
            blank_line = 1;
        } else {
            blank_line = 0;
            printf("%s", whitespace);
            for (int i = 0; i < MAX_SPACE_RUN + 1; i++)
                whitespace[i] = 0;
            ix = 0;
            putchar(c);
        }
    }
    printf("\n");
}
