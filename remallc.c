#include "shell.h"

/**
 * mem_set - fills memory with a constant byte
 * @ptr:pointer to  memory area
 * @b: the byte
 * @n: byte size
 * Return:pointer to the memory area
 */

char *_memset(char *ptr, char b, unsigned int n)
{
	unsigned int p;

	for (p = 0; p < n; p++)
		ptr[p] = b;
	return (ptr);
}

/**
 * ffree - frees a string of strings
 * @tp: string of strings
 */

void ffree(char **tp)
{
	char **a = tp;

	if (!tp)
		return;
	while (*tp)
		free(*tp++);
	free(a);
}

/**
 * _realloc - reallocates memory
 * @ptr: pointer to previous malloc
 * @od_size: byte size of previous 
 * @nw_size: byte size of new block
 * Return: pointer to new size
 */

void *_realloc(void *ptr, unsigned int od_size, unsigned int nw_size)
{
	char *y;

	if (!ptr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(ptr), NULL);
	if (nw_size == od_size)
		return (ptr);

	p = malloc(nw_size);
	if (!y)
		return (NULL);

	od_size = od_size < nw_size ? od_size : nw_size;
	while (od_size--)
		y[od_size] = ((char *)ptr)[od_size];

	free(ptr);
	return (y);
}
