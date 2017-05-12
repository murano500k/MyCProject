#include <stdio.h>
#include <stdlib.h>

/* Use tab stops given as arguments or the default tab size otherwise.  The 
 * default tab size is also used after the last tab stop has been reached.  
 * The input is supposed to use the default tab size.
 */

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
    int c;
    while ((c = getchar()) && c != EOF) {
        if (c == '\t') {
            int new_column = next_tab_stop(column, argc, argv);
            for (int spaces = new_column - column; spaces > 0; spaces--)
                putchar(' ');
            column = new_column;
        }
        else if (c == '\n') {
            column = 0;
            putchar(c);
        }
        else {
            column++;
            putchar(c);
        }
    }
}
