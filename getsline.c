#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @data: parameter struct
 * @buf: & of buffer
 * @len: & of len var
 * Return: bytes read
 */

ssize_t input_buf(data_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t lp = 0;

	if (!*len)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(data, buf, &lp);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			data->linecount_flag = 1;
			comments_off(*buf);
			make_history_list(data, *buf, data->histcount++);
			{
				*len = r;
				data->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @data: parameter struct
 * Return: bytes read
 */

ssize_t get_input(data_t *data)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(data, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len) 
	{
		j = i;
		p = buf + i;

		chk_chain(data, buf, &j, i, len);
		while (j < len) 
		{
			if (is_chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buf: buffer
 * @i: buf size
 * Return: r
 */
ssize_t read_buf(data_t *data, char *buf, size_t *i)
{
	ssize_t p = 0;

	if (*i)
		return (0);
	p = read(data->readfd, buf, READ_BUF_SIZE);
	if (p >= 0)
		*i = p;
	return (p);
}

/**
 * _getline - gets the next line of input from STDIN
 * @data: parameter struct
 * @ptr: address of pointer to buffer
 * @length: size of  ptr buffer if not NULL
 * Return: var s
 */

int _getline(data_t *data, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t g;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + g : g + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @signum: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
