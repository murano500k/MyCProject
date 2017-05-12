#include <stdio.h>

int main()
{
    int letters[26];
    for (int i = 0; i < 26; i++)
        letters[i] = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (c >= 65 && c <= 90)
            letters[c - 65]++;
        if (c >= 97 && c <= 122)
            letters[c - 32 - 65]++;
    }

    for (int i = 0; i < 26; i++) {
        printf(" %c: ", i + 65);
        for (int j = 0; j < letters[i]; j++)
            printf(".");
        printf("\n");
    }
}