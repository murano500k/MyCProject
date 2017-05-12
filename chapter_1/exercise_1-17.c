#include <stdio.h>

#define MAXLINE  80

int get_line(char s[], int lim);
int get_line_old(char s[], int lim);
void copy(char from[], char to[]);

int main()
{
    int len = 0;
    char line[MAXLINE + 2];

    for (int i = 0; i < MAXLINE + 2; i++)
        line[i] = 0;

    while ((len = get_line(line, MAXLINE + 1)) > 0) {
        int len_exc_newline = line[len - 1] == '\n' ? len - 1 : len;
        if (len_exc_newline == MAXLINE + 1) {
            printf("%s", line);
            int c;
            while ((c = getchar()) != EOF && c != '\n') {
                putchar(c);
            }
            putchar('\n');
        }
    }

    return 0;
}
