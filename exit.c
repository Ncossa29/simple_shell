#include "shell.h"

/**
 **_strncat - concatenates two strings
 *@fst: string 1
 *@ndst: string 2
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *fst, char *ndst, int n)
{
	int i, j;
	char *s = fts

	i = 0;
	j = 0;
	while (fts[i] != '\0')
		i++;
	while (ndst[j] != '\0' && j < n)
	{
		fts[i] = ndst[j];
		i++;
		j++;
	}
	if (j < n)
		fts[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char p)
{
	do {
		if (*s == p)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
