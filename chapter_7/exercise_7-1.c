/*

Write a program that converts upper case to lower or lower case to upper,
depending on the name it is invoked with, as found in argv[0].


*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char  *argv[])
{
    int (*case_changer)(int);
    int c;
    if (argv[1]!=NULL && strcmp(argv[1], "-l") == 0){
        case_changer = tolower;
    } else
        case_changer = toupper;

    while ((c = getchar()) != EOF)
        putchar(case_changer(c));

    return 0;
}
