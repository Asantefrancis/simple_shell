#include "shell.h"

/**
 * prompt_user - Prompts the user for input
 */
void prompt_user(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "cisfun$ ", 8);
}

/**
 * read_cmd - Reads user command
 * @command: Buffer that stores the command received from the user
 */
void read_cmd(char *command)
{
	size_t n = 0;
	ssize_t num_char;

	num_char = getline(&command, &n, stdin);
	if (num_char == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}

	if (command[num_char - 1] == '\n')
		command[num_char - 1] = '\0';
}

/**
 * execute_cmd - Executes the user's command
 * @command: The command to execute
 */
void execute_cmd(char *command)
{
	char *args[BUFFER_SIZE];
	int arg_index = 0, status;
	pid_t child_pid;
	char *token = strtok(command, " ");

	while (token != NULL)
	{
		args[arg_index++] = token;
		token = strtok(NULL, " ");
	}
	args[arg_index] = NULL;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}

