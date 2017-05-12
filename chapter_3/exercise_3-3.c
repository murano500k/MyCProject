/*

Write a function expand(s1,s2) that expands shorthand notations like a-z in the
string s1 into the equivalent complete list abc..xyz in s2. Allow for letters 
of either case and digits, and be prepared to handle cases like a-b-c and 
a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally.

*/

#include <stdio.h>

int lowercase_pair(int c1, int c2);
int lowercase_pair(int c1, int c2)
{
    return (c1 >= 'a' && c1 <= 'z') &&
           (c2 >= 'a' && c2 <= 'z');
}

int uppercase_pair(int c1, int c2);
int uppercase_pair(int c1, int c2)
{
    return (c1 >= 'A' && c1 <= 'Z') &&
           (c2 >= 'A' && c2 <= 'Z');
}

int digit_pair(int c1, int c2);
int digit_pair(int c1, int c2)
{
    return (c1 >= '0' && c1 <= '9') &&
           (c2 >= '0' && c2 <= '9');
}

void expand(char* s1, char* s2);
void expand(char* s1, char* s2)
{
    int i = 0;
    int j = 0;

    while (s1[i] != '\0') {
        int start = s1[i];
        s2[j++] = s1[i++];

        if (s1[i] == '-') {
            if (s1[i + 1] != '\0') {
                int end = s1[i + 1];
                if (start < end &&
                    (lowercase_pair(start, end) ||
                     uppercase_pair(start, end) ||
                     digit_pair(start, end))) {
                    for (int c = start + 1; c <= end; c++) {
                        s2[j] = (char) c;
                        j++;
                    }
                    i += 2;
                }
            }
        }
    }
    s2[j] = '\0';
}

int main()
{
    char target[] = "                                                                                                                                                                                                                                                                        ";

    char s1[] = "   a-e    2-9";
    char s2[] = "-f-l123a-b-c a-e-z x-z0-9";

    char t1[] = "   abcde    23456789";
    char t2[] = "-fghijkl123ab-c abcde-z xyz0123456789";

    expand(s1, target);
    printf("\ntest 1:\n%s\n%s\n%s\n", s1, t1, target);

    expand(s2, target);
    printf("\ntest 2:\n%s\n%s\n%s\n", s2, t2, target);

}