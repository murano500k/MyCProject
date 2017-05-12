#include <stdio.h>

int any(char*, char*);
void test(char*, char*);

void test(char* a, char* b)
{
    printf("any(\"%s\", \"%s\") = %d\n", a, b, any(a, b));
}

int any(char* a, char* b)
{
    for (int i = 0; a[i] != '\0'; i++)
        for (int j = 0; b[j] != '\0'; j++)
            if (b[j] == a[i])
                return i;
    return -1;
}

int main()
{
    test("abc", "ba");
    test("abc", "iupuwerwerb");
    test("abc", "d");
}