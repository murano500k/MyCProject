#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF) {
        printf("%d %d\n", c, c != EOF);
    }
    printf("%d %d\n", c, c != EOF);
}