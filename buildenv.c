#include "shell.h"

int nk_env(char **args, char __attribute__((__unused__)) **front);
int nk_setenv(char **args, char __attribute__((__unused__)) **front);
int nk_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * nk_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Return: If an error occurs - -1.
 * Description: Prints one variable per line in the
 */

int nk_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * nk_setenv -adds an environmental or Changes variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */

int nk_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_data;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_data = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_data)
		return (create_error(args, -1));
	_strcpy(new_data, args[0]);
	_strcat(new_data, "=");
	_strcat(new_data, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_data;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_data);
		return (create_error(args, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_data;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * nk_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 * Return: If an error occurs - -1. value
 */

int nk_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
