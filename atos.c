#include "shell.h"

/**
 * active - returns true if shell is interactive mode
 * @data: struct address
 * Return: 1 if interactive mode, 0 otherwise
 */

int active(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * isdelim - checks for delimeter
 * @c: the char to be checked
 * @delim: the string
 * Return: 1 if true, 0 if false
 */

int isdelim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * the_alpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int the_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *g)
{
	int t, sign = 1, flag = 0, op;
	unsigned int result = 0;

	for (t = 0; g[t] != '\0' && flag != 2; t++)
	{
		if (g[t] == '-')
			sign *= -1;

		if (g[t] >= '0' && g[t] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (g[t] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		op = -result;
	else
		op = result;

	return (op);
}
