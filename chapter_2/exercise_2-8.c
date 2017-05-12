#include <stdio.h>
#include <limits.h>

void print_bits(unsigned int x);
void print_bits(unsigned int x)
{
    char s[] = "00000000000000000000000000000000";
    for (int i = 0; i < 32; i++) {
        if ((x & 1) != 0)
            s[31 - i] = '1';
        else
            s[31 - i] = '0';
        x = x >> 1;
    }
    printf("%s", s);
}

unsigned int rightrot(unsigned int x, int n);
unsigned int rightrot(unsigned int x, int n)
{
    unsigned int right_mask    = ~((unsigned) ~0 << n);
    unsigned int left_mask     = ~right_mask;
    unsigned int right         = x & right_mask;
    unsigned int left          = x & left_mask;
    unsigned int right_rotated = right << ((int) (sizeof x)*8 - n);
    unsigned int left_rotated  = left >> n;
    return right_rotated | left_rotated;
}

void test_rightrot(unsigned int x, int n);
void test_rightrot(unsigned int x, int n)
{
    printf("rightrot(");
    print_bits(x);
    printf(", %d) = ", n);
    print_bits(rightrot(x, n));
    printf("\n");
}

int main()
{
    unsigned int p = 5;
    printf("sizeof(unsigned int) in bytes = %lu\n", sizeof p);
    printf("sizeof(unsigned int) in bits = %lu\n", (sizeof p)*8);
    test_rightrot(245-64 + 65536, 4);
    test_rightrot(UINT_MAX, 4);
}