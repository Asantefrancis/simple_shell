#include "shell.h"

/**
 * main - Entry point of the program
 * @ac: The number of command-line arguments
 * @av: Array of command-line argument strings
 * @env: Array of environment variable strings
 *
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	if (ac == 1)
		prompt(av, env);

	return (0);
}

