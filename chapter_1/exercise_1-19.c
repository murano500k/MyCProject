#include <stdio.h>

#define MAXLINE 80

void reverse(char in[], char out[]);
int get_line(char line[], int lim);

int main()
{
    char line[MAXLINE + 2];
    char revline[MAXLINE + 2];
    int len;
    while ((len = get_line(line, MAXLINE)) > 0) {
        reverse(line, revline);
        printf("%s", revline);
    }
}


void reverse(char in[], char out[])
{
    int i, j;

    for (i = 0; in[i] != 0; i++)
        ;

    for (j = 0; j < i; j++)
        out[j] = in[i - j - 1];
    out[j] = 0;
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