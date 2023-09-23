#include "shell.h"

int nk_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *data);
void print_alias(alias_t *alias);

/**
 * nk_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * Return: If an error occurs - -1
 */

int nk_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *data;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		data = _strchr(args[i], '=');
		if (!data)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], data);
	}
	return (ret);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @data: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *data)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_data;

	*data = '\0';
	data++;
	len = _strlen(data) - _strspn(data, "'\"");
	new_data = malloc(sizeof(char) * (len + 1));
	if (!new_data)
		return;
	for (j = 0, k = 0; data[j]; j++)
	{
		if (data[j] != '\'' && data[j] != '"')
			new_data[k++] = data[j];
	}
	new_data[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->data);
			temp->data = new_data;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_data);
}

/**
 * print_alias - Prints the alias in the format name='data'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->data) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->data);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_data;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->data) == 0)
			{
				new_data = malloc(sizeof(char) * (_strlen(temp->data) + 1));
				if (!new_data)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_data, temp->data);
				free(args[i]);
				args[i] = new_data;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
