#include "shell.h"

/**
 * _strlen - length of a string
 * @s: the string 
 * Return: integer length of string
 */

int _strlen(char *s)
{
	int p = 0;

	if (!s)
		return (0);

	while (*s++)
		p++;
	return (p);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @s2: the second strang
 * Return: negative if s1 < s2
 */

int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with hay
 * @haystack: string to search
 * @needle: the sub-string to find
 * Return: address of next char 
 */

char *starts_with(const char *hay, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: pointer to destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
