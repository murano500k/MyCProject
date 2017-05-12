#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int);
void debugbuf(void);
int getint(int *);

int main()
{
    int i;

    printf(">> ");
    if (getint(&i)) {
        printf("got: %d\n", i);
    } else {
        printf("not a number\n");
    }
    debugbuf();
}

int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); // it's not a number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        int c1 = c;
        c = getch();
        if (!isdigit(c)) {
            ungetch(c);
            ungetch(c1);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
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
