#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * nk_print - Prints a string to stdout.
 * @printfunction: The string to be printed.
 */
void nk_print(const char *printfunction);

/**
 * flash_prompt - Displays a shell prompt.
 */
void flash_prompt(void);

/**
 * scan_command - Scans user input into a command buffer.
 * @command: A buffer to store the user's input.
 * @size: The size of the command buffer.
 */
void scan_command(char *command, size_t size);

/**
 * enforce_command - Enforces a command to be executed.
 * @command: The command to be executed.
 */
void enforce_command(const char *command);

#endif
