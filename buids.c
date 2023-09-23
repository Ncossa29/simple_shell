#include "shell.h"

/**
 * nk_exit - exits the shell
 * @data: Used to maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if data.argv[0] not ="exit"
 */

int nk_exit(data_t *data)
{
	int exitchck;

	if (data->argv[1])
	{
		exitchck = err_atoi(data->argv[1]);
		if (exitchck == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = err_atoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * nk_cd - changes the current directory of the process
 * @data: Structure containing arguments. 
 * Return: Always 0
 */

int nk_cd(data_t *data)
{
	char *s, *dir, buffer[1034];
	int chdir_ret;

	s = getcwd(buffer, 1034);
	if (!s)
		_puts("./hsh \n");
	if (!data->argv[1])
	{
		dir = get_env(data, "root=");
		if (!dir)
			chgdir_ret = chdir((dir = get_env(data, "PWD=")) ? dir : "/");
		else
			chgdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!get_env(data, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(data, "OLDPWD=")), _putchar('\n');
		chgdir_ret =	chdir((dir = get_env(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chgdir_ret = chdir(data->argv[1]);
	if (chgdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		nk_setenv(data, "OLDPWD", get_env(data, "PWD="));
		nk_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * nk_help - changes the current directory of the process
 * @data: Used to maintain constant function prototype.
 * Return: Always 0
 */

int nk_help(data_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
