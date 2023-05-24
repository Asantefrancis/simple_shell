#include "shell.h"

/**
 * main - Main entry for built shell.
 *
 * Return: Always 0
 */
int main(void)
{
	char *command = NULL;

	while (1)
	{
		prompt_user();
		read_cmd(command);
		execute_cmd(command);
	}
	free (command);
	return (0);
}
