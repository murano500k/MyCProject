
#include <stdio.h>

void test(char s[]);
int htoi(char s[]);

int main()
{
    test("11");
    test("a");
    test("1a");
    test("0x11");
}

void test(char s[])
{
    printf("%5s = %d\n", s, htoi(s));
}

int htoi(char s[])
{
    int end = 0;
    for (; s[end] != 0; end++)
        ;
    end--;

    int acc = 0;
    int exponent = 1;

    for (; end >= 0 && !(end == 1 && (s[end] == 'x' || s[end] == 'X')); end--) {
        int val = 0;

        int l = s[end];
        if (l >= 48 && l <= 57)
            val = l - 48;
        else if (l >= 65 && l <= 90)
            val = l - 65 + 10;
        else if (l >= 97 && l <= 102)
            val = l - 97 + 10;

        acc += exponent * val;
        exponent *= 16;
    }
    return acc;
}