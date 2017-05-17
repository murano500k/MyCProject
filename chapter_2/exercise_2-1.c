#include <stdio.h>
#include <limits.h>
#include <float.h>

int main ()
{
    long l;
    int i, j, k, m;
    float f, g, h;
    l = 1;
    while (2 * l + 1 > l)
        l = 2 * l + 1;
    printf("LONG_MAX: %ld (%ld)\n", l, LONG_MAX);
    printf("LONG_MIN: %ld (%ld)\n", -l - 1, LONG_MIN);
    i = 0;
    f = 1.0f;
    while (f * 2.0f != f) {
        i++;
        f = f * 2.0f;
    }
    printf("FLT_MAX_EXP: %d (%d)\n", i, FLT_MAX_EXP);
    printf("FLT_MIN_EXP: %d (%d)\n", -i + 3, FLT_MIN_EXP);
    f = 1.0f;
    for (j = 1; j < i; j++)
        f = f * 2.0f;
    j = i;
    m = 0;
    g = f;
    for ( ; ; ) {
        j--;
        h = 1.0f;
        for (k = 1; k < j; k++)
            h = h * 2.0f;
        if (g + h == g)
            break;
        f = g;
        g = g + h;
        m++;
    }
    printf("FLT_MAX: %g (%g)\n", f, FLT_MAX);
    f = 1.0f;
    for (j = 0; j < i - 2; j++)
        f = f / 2.0f;
    printf("FLT_MIN: %g (%g)\n", f, FLT_MIN);
    f = 1.0f;
    for (i = 0; i < m - 1; i++)
        f = f / 2.0f;
    printf("FLT_EPSILON: %g (%g)\n", f, FLT_EPSILON);

    return 0;
}