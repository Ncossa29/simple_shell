#include "shell.h"
/**
 * nk_print - Prints a string to stdout.
 * @printfunction: The string to be printed.
 */
void nk_print(const char *printfunction)
{
	write(STDOUT_FILENO, printfunction, strlen(printfunction));
}
