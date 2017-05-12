#include <stdio.h>

#define MAX_LINE 80

int main()
{
    char buffer[MAX_LINE + 2];
    int i = 0;
    int column = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (column == MAX_LINE && c != '\n') {
            if (i < MAX_LINE)
                putchar('\n');
            for (int j = 0; j < i; j++)
                putchar(buffer[j]);
            if (i == MAX_LINE)
                putchar('\n');
            column = i;
            if (column == MAX_LINE)
                column = 0;
            i = 0;
        }

        if (c == ' ' || c == '\n') {
            for (int j = 0; j < i; j++)
                putchar(buffer[j]);
            i = 0;
            putchar(c);
        } else {
            buffer[i++] = (char) c;
        }

        if (c == '\n')
            column = 0;
        else
            column++;
    }
    for (int j = 0; j < i; j++)
        putchar(buffer[j]);
}