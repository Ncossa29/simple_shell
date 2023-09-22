#include "shell.h"
#include <sys/wait.h>
/**
 * enforce_command - Enforces a command to be executed.
 * @command: The command to be executed.
 */
void enforce_command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == 0)
	{
		if (execlp(command, command, (char *)NULL) == -1)
		{
			perror("./hsh");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
