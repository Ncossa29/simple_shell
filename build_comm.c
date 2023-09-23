#include "shell.h"

/**
 * nk_history - displays the history list, 
 * @data: Structure containing potential arguments
 *  Return: Always 0
 */

int nk_history(data_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * nk_unsetalias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int nk_unsetalias(data_t *data, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * nk_setalias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */

int nk_setalias(data_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (nk_unsetalias(data, str));

	nk_unsetalias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * nk_alias - mimics the alias builtin
 * @data: Used to maintain constant function prototype.
 *  Return: Always 0
 */

int nk_alias(data_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _strchr(data->argv[i], '=');
		if (p)
			nk_setalias(data, data->argv[i]);
		else
			print_alias(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}
