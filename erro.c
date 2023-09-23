#include "shell.h"

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */

void _eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		i++;
	}
}

/**
 * _eputchar - writes c to stderr
 * @c: The character to print
 * Return: On success 1.
 */

int _eputchar(char c)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(2, buf, b);
		b = 0;
	}
	if (c != BUF_FLUSH)
		buf[b++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given filed
 * @c: The character to print
 * @filed: The filedescriptor to write to
 * Return: * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int filed)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filed, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: string to be printed
 * @filed: the filedescriptor to write to
 * Return: the number of chars put
 */

int _putsfd(char *str, int filed)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, filed);
	}
	return (i);
}
