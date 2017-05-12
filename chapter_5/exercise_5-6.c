#include <stdio.h>
#include <stdlib.h>

int get_line(char *s, int lim);
int get_line(char *s, int lim)
{
    int c = 0;
    int i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        *s++ = (char) c;
    if (c == '\n') {
        *s++ = (char) c;
        ++i;
    }
    *s = '\0';
    return i;
}

int my_atoi(char *s);
int my_atoi(char *s)
{
    int n = 0;
    for (; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

void reverse(char *s);
void reverse(char *s)
{
    char *t = s;
    while (*t++);
    t -= 2;
    while (t > s) {
        char tmp = *t;
        *t = *s;
        *s = tmp;
        s++;
        t--;
    }
}

void my_itoa(int n, char *s);
void my_itoa(int n, char *s)
{
    int sign = n;
    char *t = s;
    do {
        *s++ = (char) abs(n % 10) + '0';
    } while (abs(n /= 10) > 0);
    if (sign < 0)
        *s++ = '-';
    *s = '\0';
    reverse(t);
}
void testreverse(char s[]);
void testreverse(char s[])
{
    printf("testreverse(\"%s\") = ", s);
    reverse(s);
    printf("\"%s\"\n", s);
}

int main()
{
    char i[] = "123";
    printf("my_atoi(\"%s\") = %d\n", i, my_atoi(i));

    char a[] = "";
    testreverse(a);

    char b[] = "x";
    testreverse(b);

    char c[] = "xy";
    testreverse(c);

    char d[] = "xyz";
    testreverse(d);

    char e[] = "0123456789";
    testreverse(e);

    char x[] = "                ";
    my_itoa(50904, x);
    printf("my_itoa(50904) = \"%s\"\n", x);
}