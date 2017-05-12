#include <stdio.h>

#define TAB_WIDTH 4

int main()
{
    int tab_width = TAB_WIDTH;
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
                int next_tab_stop = (start_of_space_run / tab_width) * tab_width + tab_width;
                if (next_tab_stop <= column) {
                    putchar('\t');
                    space_run -= next_tab_stop - start_of_space_run;
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