#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings
 */

char **strtow(char *str, char *del)
{
	int i, h, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isdelim(str[i], del) && (isdelim(str[i + 1], del) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0,  = 0; h < numwords; h++)
	{
		while (isdelim(str[i], del))
			i++;
		k = 0;
		while (!isdelim(str[i + k], del) && str[i + k])
			k++;
		s[h] = malloc((k + 1) * sizeof(char));
		if (!s[h])
		{
			for (k = 0; k < h; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[h][m] = str[i++];
		s[h][m] = 0;
	}
	s[h] = NULL;
	return (s);
}

/**
 * **strto - splits a string into words
 * @str: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strto(char *str, char del)
{
	int i, j, k, p, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
				    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		k = 0;
		while (str[i + k] != del && str[i + k] && str[i + k] != del)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (p = 0; p < k; p++)
			s[j][p] = str[i++];
		s[j][p] = 0;
	}
	s[j] = NULL;
	return (s);
}
