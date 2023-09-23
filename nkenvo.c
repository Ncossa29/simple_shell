
#include "shell.h"

/**
 * nk_env - prints the current environment
 * @data: Structure containing potential arguments
 * Return: Always 0
 */

int nk_env(data_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @data: Used to maintain
 * @name: env var name
 * Return: the value
 */

char *get_env(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = starts_with(node->alis, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * nk_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @data: Structure containing potential arguments.
 *  Return: Always 0
 */

int nk_setenv(data_t *data)
{
	if (data->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (nk_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * nk_unsetenv - Remove an environment variable
 * @data:  Used to maintain Function prototype.
 * Return: Always 0
 */

int nk_unsetenv(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_eputs("error.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		nk_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * env_list - populates env linked list
 * @data: arguments. Used to maintain function prototype.
 * Return: Always 0
 */

int env_list(data_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}
