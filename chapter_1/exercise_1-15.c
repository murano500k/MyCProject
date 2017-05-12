#include <stdio.h>

#define UPPER  300
#define LOWER  0
#define STEP   20

double fahr_to_celsius(int fahr);
double fahr_to_celsius(int fahr) {
    return (5.0/9.0)*(fahr-32);
}

int main()
{
    for (int fahr = LOWER; fahr <= UPPER; fahr += STEP)
        printf(" %3d %6.1f\n", fahr, fahr_to_celsius(fahr));
}