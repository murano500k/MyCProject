/* Removes comments from a C program (both styles) */

#include <stdio.h>

int main()
{
    int in_c_comment = 0;
    int in_cpp_comment = 0;
    int in_string = 0;
    int in_character_literal = /* eg */0;
    int c;
    int prevc = 0;
    while ((c = getchar()) != EOF) {
        if (!in_c_comment && !in_cpp_comment &&
            !in_string && !in_character_literal) {
            if (prevc == '/' && c == '*')
                in_c_comment = 1;
            if (c == '/' && prevc == '/')
                in_cpp_comment = 1;
        }

        if (c == '"') {
            if (in_string) {
                if (prevc != '\\')
                    in_string = 0;
            } else if (!in_c_comment && !in_cpp_comment && !in_character_literal) {
                in_string = 1;
            }
        }


        if (c == '\'') {
            if (in_character_literal) {
                if (prevc != '\\')
                    in_character_literal = 0;
            } else if (!in_c_comment && !in_cpp_comment && !in_string) {
                in_character_literal = 1;
            }
        }

        if (!in_c_comment && !in_cpp_comment && prevc)
            putchar(prevc);

        if (in_c_comment)
            if (prevc == '*' && c == '/') {
                in_c_comment = 0;
                c = 0;
            }
        if (in_cpp_comment)
            if (c == '\n')
                in_cpp_comment = 0;

        prevc = c;
    }
}
