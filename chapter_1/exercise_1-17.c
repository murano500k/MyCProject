#include <stdio.h>

#define MAXLINE		1000
#define DISPLAY_LENGTH	80

int 	mygetline (char line[], int limit);

int main ()

{
	int	len;
	char	line[MAXLINE];

	while ((len = mygetline(line, MAXLINE)) > 0)

		if (len > DISPLAY_LENGTH)

			printf("%s", line);

	return 0;
}

int mygetline (char line[], int limit)

{
	int	i, c;

	for (i = 0; 
		i < limit - 1 && (c = getchar()) != '\n';
		i++)

		line[i] = c;

	if (c == '\n') {

		line[i] = c;
		i++;

	}
	line[i] = '\0';

	return i;
}
