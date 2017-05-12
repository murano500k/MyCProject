/*

In a two's complement number representation, the first version of itoa
does not handle the largest negative number, i.e. -2**(wordsize-1).

*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void reverse(char s[]);
void reverse(char s[])
{
    int c, i, j;

    for (i = 0, j = (int) strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = (char) c;
    }
}

void myitoa(int n, char s[]);
void myitoa(int n, char s[])
{
    int i, sign;

    sign = n;
    i = 0;
    do {
        s[i++] = (char) abs(n % 10) + '0';
    } while (abs(n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char s[] = "                                          ";

    printf("\nfixed itoa:\n");
    myitoa(INT_MIN + 1, s);
    printf("%d: %s\n", INT_MIN + 1, s);
    myitoa(INT_MIN, s);
    printf("%d: %s\n", INT_MIN, s);

}