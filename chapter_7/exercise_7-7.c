/*

Modify the pattern finding program to take its input from a set of named files
or, if no files are named as arguments, from the standard input. Should the
file name be printed when a matching line is found?

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

int get_line(FILE *fp, char *s, int lim);
int get_line(FILE *fp, char *s, int lim)
{
    int c = 0;
    int i;
    for (i = 0; i < lim - 1 && (c = fgetc(fp)) != EOF && c != '\n'; ++i)
        *s++ = (char) c;
    if (c == '\n') {
        *s++ = (char) c;
        ++i;
    }
    *s = '\0';
    return i;
}

static int except = 0;
static int number = 0;
static int found = 0;

void find_in(char *filename, char *pattern, FILE *fp);
void find_in(char *filename, char *pattern, FILE *fp)
{
    char line[MAXLINE];
    long lineno = 0;
    while (get_line(fp, line, MAXLINE) > 0) {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except) {
            if (filename != NULL)
                printf("%s:", filename);
            if (number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
}

int main(int argc, char *argv[])
{
    int c;
    char *progname = argv[0];
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch(c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }

    if (*argv == NULL)
        printf("Usage: find -x -n pattern [FILE]+\n");
    else {
        char *pattern = *argv;

        int given_files = 0;
        while (*++argv) {
            given_files = 1;
            char *filename = *argv;
            FILE *fp = fopen(filename, "r");
            if (fp == NULL) {
                fprintf(stderr, "%s: can't open file %s\n", progname, filename);
                exit(1);
            }
            find_in(filename, pattern, fp);
        }
        if (!given_files)
            find_in(NULL, pattern, stdin);
    }
    return found;
}
