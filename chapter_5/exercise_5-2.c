#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
void debugbuf(void);
int getint(int *);

int getfloat(double *pd);
int getfloat(double *pd)
{
    int sign;
    int c;

    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();

    while (isdigit(c)) {
        *pd = 10 * *pd + (c - '0');
        c = getch();
    }
    int den = 1;
    if (c == '.') {
        c = getch();
        while (isdigit(c)) {
            *pd = 10 * *pd + (c - '0');
            den *= 10;
            c = getch();
        }
    }
    *pd /= den;
    *pd *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main()
{
    double d;
    printf(">> ");
    if (getfloat(&d)) {
        printf("got: %g\n", d);
    } else {
        printf("not a number\n");
    }
    debugbuf();
}


#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = (char) c;
}

void debugbuf()
{
    printf("buf: [");
    for (int i = 0; i < bufp; i++)
        printf("%d, ", buf[i]);
    printf("]\n");
}