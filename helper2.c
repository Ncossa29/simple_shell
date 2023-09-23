#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *n_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 */

void handle_line(char **line, ssize_t read)
{
	char *old_line, *n_line;
	char previous, current, next;
	size_t i, j;
	ssize_t n_len;

	n_len = get_new_len(*line);
	if (n_len == read - 1)
		return;
	n_line = malloc(n_len + 1);
	if (!n_line)
		return;
	j = 0;
	old_line = *line;
	for (i = 0; old_line[i]; i++)
	{
		current = old_line[i];
		next = old_line[i + 1];
		if (i != 0)
		{
			previous = old_line[i - 1];
			if (current == ';')
			{
				if (next == ';' && previous != ' ' && previous != ';')
				{
					n_line[j++] = ' ';
					n_line[j++] = ';';
					continue;
				}
				else if (previous == ';' && next != ' ')
				{
					n_line[j++] = ';';
					n_line[j++] = ' ';
					continue;
				}
				if (previous != ' ')
					n_line[j++] = ' ';
				n_line[j++] = ';';
				if (next != ' ')
					n_line[j++] = ' ';
				continue;
			}
			else if (current == '&')
			{
				if (next == '&' && previous != ' ')
					n_line[j++] = ' ';
				else if (previous == '&' && next != ' ')
				{
					n_line[j++] = '&';
					n_line[j++] = ' ';
					continue;
				}
			}
			else if (current == '|')
			{
				if (next == '|' && previous != ' ')
					n_line[j++]  = ' ';
				else if (previous == '|' && next != ' ')
				{
					n_line[j++] = '|';
					n_line[j++] = ' ';
					continue;
				}
			}
		}
		else if (current == ';')
		{
			if (i != 0 && old_line[i - 1] != ' ')
				n_line[j++] = ' ';
			n_line[j++] = ';';
			if (next != ' ' && next != ';')
				n_line[j++] = ' ';
			continue;
		}
		n_line[j++] = old_line[i];
	}
	n_line[j] = '\0';

	free(*line);
	*line = n_line;
}

/**
 * get_new_len - Gets the new length 
 * @line: The line to check.
 * Return: The new length of the line.
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t n_len = 0;
	char current, next;

	for (i = 0; line[i]; i++)
	{
		current = line[i];
		next = line[i + 1];
		if (current == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (current == ';')
			{
				if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					n_len += 2;
					continue;
				}
				else if (line[i - 1] == ';' && next != ' ')
				{
					n_len += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					n_len++;
				if (next != ' ')
					n_len++;
			}
			else
				logical_ops(&line[i], &n_len);
		}
		else if (current == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				n_len++;
			if (next != ' ' && next != ';')
				n_len++;
		}
		n_len++;
	}
	return (n_len);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @n_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *n_len)
{
	char previous, current, next;

	previous = *(line - 1);
	current = *line;
	next = *(line + 1);

	if (current == '&')
	{
		if (next == '&' && previous != ' ')
			(*n_len)++;
		else if (previous == '&' && next != ' ')
			(*n_len)++;
	}
	else if (current == '|')
	{
		if (next == '|' && previous != ' ')
			(*n_len)++;
		else if (previous == '|' && next != ' ')
			(*n_len)++;
	}
}
