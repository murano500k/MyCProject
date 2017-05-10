#include <stdio.h>


main ()

{
	int	c;

	c = getchar() != EOF;
	printf("c = getchar() != EOF is %d\n", c);
}
