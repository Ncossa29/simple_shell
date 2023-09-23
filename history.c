#include "shell.h"

/**
 * get_history_file - gets the history file
 * @data: parameter struct
 * Return: allocated string containg history file
 */

char *get_history_file(data_t *data)
{
	char *buf, *dir;

	dir = get_env(data, "root");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file
 * @data: the parameter struct
 * Return: 1 on success
 */

int write_history(data_t *data)
{
	ssize_t fd;
	char *filename = get_history_file(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(data->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @data: the parameter
 * Return: history count on success
 */

int read_history(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, dsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		data = st.st_size;
	if (dsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (dsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, dsize);
	buf[dsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < dsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}

/**
 * make_history_list - adds entry to a history linked list
 * @data: Structure containing potential arguments
 * @buf: the buffer
 * @linecount: the history linecount, histcount
 * Return: Always 0
 */

int make_history_list(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @data: Structure containing potential arguments. Used to maintain
 * Return: the new histcount
 */

int renumber_history(data_t *data)
{
	list_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}
