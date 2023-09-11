#include "shell.h"
/**
 * scan_command - Scans user input into a command buffer.
 * @command: A buffer to store the user's input.
 * @size: The size of the command buffer.
 */
void scan_command(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			nk_print("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			nk_print("Error while reading input.\n");
			exit(EXIT_FAILURE);
		}
	}
	command[strcspn(command, "\n")] = '\0';
}
