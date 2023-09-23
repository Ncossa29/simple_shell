#include "shell.h"

/**
 * hsh - main shell loop
 * @data: the parameter & return data struct
 * @av: main argument vector
 * Return: 0 on success, 1 
 */

int hsh(data_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (active(data))
			_puts("nkshell$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(data);
		if (r != -1)
		{
			set_data(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (active(data))
			_putchar('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!active(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a the builtin command
 * @data: the parameter & return data
 * Return: -1 if builtin not found,
 */

int find_builtin(data_t *data)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", nk_exit},
		{"env", nk_env},
		{"help", nk_help},
		{"history", nk_history},
		{"set env", nk_setenv},
		{"unsetenv", nk_unsetenv},
		{"cd", nk_cd},
		{"alias", nkalias},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(data->argv[0], builtintbl[j].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[j].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - searches a command in PATH
 * @data: the parameter & return data struct
 * Return: void
 */
void find_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!isdelim(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, get_env(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		fork_cmd(data);
	}
	else
	{
		if ((active(data) || get_env(data, "PATH=")
					|| data->argv[0][0] == '/') && nk_cmd(data, data->argv[0]))
			fork_cmd(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return data struct
 * Return: void
 */

void fork_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, get_environ(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
