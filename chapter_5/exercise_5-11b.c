#include <stdio.h>
#include <ctype.h>

#define DEFAULT_TAB_WIDTH  4

int to_i(char *s, int *val);
int to_i(char *s, int *val)
{
    *val= 0;
    int got = 0;
    for (; isdigit(s[0]); s++) {
        got = 1;
        *val *= 10;
        *val += s[0] - '0';
    }
    return got;
}

int next_tab_stop(int col, int argc, char *argv[]);
int next_tab_stop(int col, int argc, char *argv[])
{
    if (argc > 1) {
        char **tab_stops = ++argv;
        while (*tab_stops) {
            int stop;
            if (to_i(*tab_stops, &stop) && stop > col) {
                return stop;
            }
            tab_stops++;
        }
    }
    return ((col + DEFAULT_TAB_WIDTH) / DEFAULT_TAB_WIDTH) * DEFAULT_TAB_WIDTH;
}


int main(int argc, char *argv[])
{
    int column = 0;
    int space_run = 0;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++space_run;
        }
        else if (c == '\n') {
            column = -1;
            space_run = 0;
            putchar(c);
        } else {
            if (space_run == 1) {
                putchar(' ');
                space_run = 0;
            }
            while (space_run > 0) {
                int start_of_space_run = column - space_run;
                int next_stop = next_tab_stop(start_of_space_run, argc, argv);
                if (next_stop <= column) {
                    putchar('\t');
                    space_run -= next_stop - start_of_space_run;
                } else {
                    for (; space_run > 0; space_run--)
                        putchar(' ');
                }
            }

            putchar(c);
        }
        ++column;
    }
}
