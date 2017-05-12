/*

Write a recursive version of itoa; that is, convert an integer into a string
by calling a recursive routine

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int itoa1(int n, char s[], int start);
int itoa1(int n, char s[], int start)
{
    char ch = (char) abs(n % 10) + '0';
    int i = (n / 10) ? itoa1(n / 10, s, start) : start;
    s[i] = ch;
    return i + 1;
}

void itoa(int n, char s[]);
void itoa(int n, char s[])
{
    int start = 0;
    if (n < 0) {
        s[0] = '-';
        start = 1;
    }
    itoa1(n, s, start);
}

void testitoa(int);
void testitoa(int n)
{
    char s[] = "                 ";
    itoa(n, s);
    printf("itoa(%d) = %s\n", n, s);
}

int main()
{
    testitoa(123);
    testitoa(56789);
    testitoa(-22);
    testitoa(1);
    testitoa(0);
}