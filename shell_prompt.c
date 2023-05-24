#include "shell.h"
#include <unistd.h>

/**
 * prompt - Display a shell prompt and execute user commands
 * @av: The command-line arguments passed to the program
 * @env: The environment variables
 */
void prompt(char **av, char **env)
{
	char *command = NULL;
	int i, status;
	size_t n = 0;
	ssize_t num_char;
	char *argv[] = {NULL, NULL};
	pid_t child_pid;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "cisfun$ ", 8);
		num_char = getline(&command, &n, stdin);
		if (num_char == -1)
		{
			free(command);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (command[i])
		{
			if (command[i] == '\n')
				command[i] = '\0';
			i++;
		}

		argv[0] = command;
		child_pid = fork();
		if (child_pid == -1)
		{
			free(command);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
			child_process(av, env, argv);
		else
			parent_process(&status);
	}
}

/**
 * child_process - Execute the command in the child process
 * @av: The command-line arguments passed to the program
 * @env: The environment variables
 * @argv: The argument vector for the command
 */
void child_process(char **av, char **env, char **argv)
{
	if (execve(argv[0], argv, env) == -1)
	{
		char *error_msg = av[0];

		while (*error_msg)
		{
			write(STDOUT_FILENO, error_msg, 1);
			error_msg++;
		}
		write(STDOUT_FILENO, ": no such file or directory\n", 28);
	}
}

/**
 * parent_process - Wait for the child process to finish in the parent process
 * @status: The exit status of the child process
 */
void parent_process(int *status)
{
	wait(status);
}

