#include "shell.h"

/**
 * main - entry point
 * description- display prompt,gets user input, prints input
 * Return (0) success
 */

int main(void)
{
	size_t j = 20;
	char *buf;

	buf = malloc(sizeof(char) * 20);
	getline(&buf, &j, stdin);
	printf("%s\n", buf);

	free(buf);

	return (0);
}
