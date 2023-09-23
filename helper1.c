#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t p;

	for (i = 0; args[p] || args[p + 1]; p++)
		free(args[i]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value to variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 * Return: If the variable is not found - an empty string..
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *v;

	v = malloc(len + 1);
	if (!v)
		return (NULL);
	var[0] = '\0';
	_strncat(v, beginning, len);

	var_addr = _getenv(var);
	free(v);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 * Description: Replaces $$ with the current PID
 */

void variable_replacement(char **line, int *exe_ret)
{
	int j, f = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				f = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				f = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (f = j + 1; old_line[f] &&
						old_line[f] != '$' &&
						old_line[f] != ' '; f++)
					;
				len = f - (j + 1);
				replacement = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[f]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replacement)
			{
				_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
