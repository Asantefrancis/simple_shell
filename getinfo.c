#include "shell.h"

/**
 * clear_shell_info - initializes shell_info_t struct
 * @info: struct address
 */
void clear_shell_info(shell_info_t *info)
{
	info->arguments = NULL;
	info->command_arguments = NULL;
	info->path = NULL;
	info->argument_count = 0;
}

/**
 * set_shell_info - initializes shell_info_t struct
 * @info: struct address
 * @arguments: argument vector
 */
void set_shell_info(shell_info_t *info, char **arguments)
{
	int i = 0;

	info->program_name = arguments[0];
	if (info->arguments)
	{
		info->command_arguments = strtow(info->arguments, " \t");
		if (!info->command_arguments)
		{
			info->command_arguments = malloc(sizeof(char *) * 2);
			if (info->command_arguments)
			{
				info->command_arguments[0] = _strdup(info->arguments);
				info->command_arguments[1] = NULL;
			}
		}
		for (i = 0; info->command_arguments && info->command_arguments[i]; i++)
			;
		info->argument_count = i;

		replace_aliases(info);
		replace_variables(info);
	}
}

/**
 * free_shell_info - frees shell_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_shell_info(shell_info_t *info, int all)
{
	ffree(info->command_arguments);
	info->command_arguments = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->aliases)
			free_list(&(info->aliases));
		ffree(info->environment_copy);
		info->environment_copy = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
