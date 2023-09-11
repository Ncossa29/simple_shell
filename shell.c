#include "shell.h"
/**
 * main - Entry point of the nk_shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char command[130];

	while (1)
	{
		scan_command(command, sizeof(command));
		enforce_command(command);
		flash_prompt();
	}

	return (0);
}
