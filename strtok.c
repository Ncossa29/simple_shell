#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter 
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: The delimiter index
 */

int token_len(char *str, char *delim)
{
	int index = 0, l = 0;

	while (*(str + index) && *(str + index) != *delim)
	{
		l++;
		index++;
	}

	return (l);
}

/**
 * count_tokens - Counts the number of delimited
 * @str: The string to be searched.
 * @delim: The delimiter character.
 * Return: The number of words contained within str.
 */

int count_tokens(char *str, char *delim)
{
	int index, tokens = 0, l = 0;

	for (index = 0; *(str + index); index++)
		l++;

	for (index = 0; index < l; index++)
	{
		if (*(str + index) != *delim)
		{
			tokens++;
			index += token_len(str + index, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 * Return: A pointer to an array containing the tokenized words.
 */

char **_strtok(char *line, char *delim)
{
	char **ptr;
	int index = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[index] == *delim)
			index++;

		letters = token_len(line + index, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (index -= 1; index >= 0; index--)
				free(ptr[index]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[index];
			index++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}
