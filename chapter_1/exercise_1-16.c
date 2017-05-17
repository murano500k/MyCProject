#include <stdio.h>

#define MAXLINE  80

int get_line(char s[], int lim);
void copy(char from[], char to[]);

int main()
{
    int len = 0;
    int max = 0;
    char longest[MAXLINE + 1];
    char line[MAXLINE + 1];

    for (int i = 0; i < MAXLINE + 1; i++)
        line[i] = longest[i] = 0;

    while ((len = get_line(line, MAXLINE)) > 0) {
        if (len > max) {
            copy(line, longest);
            max = len;
        }
    }

    if (max > 0) {
        if (max <= MAXLINE)
            longest[max - 1] = 0;
        printf("length of longest line: %d\n", max);
        printf("%s\n", longest);
    }

    return 0;
}

int get_line(char s[], int lim)
{
    int c;
    int i = 0;
    while((c = getchar()) != EOF) {
        if (c == '\n') {
            s[i] = '\n';
            s[i + 1] = 0;
            return i + 1;
        }
        s[i] = (char) c;
        i++;
        if (i == lim) {
            while ((c = getchar()) != EOF && c != '\n')
                i++;
            return i;
        }
    }
    s[i + 1] = 0;
    return i;
}

void copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != 0)
        ++i;
}