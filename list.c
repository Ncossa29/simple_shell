#include "shell.h"

/**
 * list_len - finds length of linked list
 * @h: pointer to first node
 * Return: size of list
 */

size_t list_len(const list_t *h)
{
	size_t p = 0;

	while (h)
	{
		h = h->next;
		p++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 * Return: array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), x;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (x = 0; x < i; x++)
				free(strs[x]);
			free(strs);
			return (NULL);
		}

		str = strcpy(str, node->str);
		strs[x] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a linked list
 * @h: pointer to first node
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t y = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		y++;
	}
	return (y);
}

/**
 * node_starts_with - returns node prefix
 * @node: pointer 
 * @prefix: string 
 * @c: the next character 
 * Return: match node 
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *t = NULL;

	while (node)
	{
		t = starts_with(node->str, prefix);
		if (t && ((c == -1) || (*t == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: list head
 * @node: the node
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t g = 0;

	while (head)
	{
		if (head == node)
			return (g);
		head = head->next;
		g++;
	}
	return (-1);
}
