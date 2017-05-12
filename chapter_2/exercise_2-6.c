#include <stdio.h>


unsigned setbits (unsigned x, int p, int n, unsigned y)
{
    y = (y & ~(~0 << n)) << (p + 1 - n);
    x = x & ~(~(~0 << n) << (p + 1 - n));
    return x | y;
}

int main ()
{
    unsigned x, y;
    int p, n;
    x = 0xf7;
    y = 0x04;
    p = 6;
    n = 3;
    printf("setbits(0x%x, %d, %d, 0x%x) = 0x%x\n",
           x, p, n, y,
           setbits(x, p, n, y));
    return 0;
}
