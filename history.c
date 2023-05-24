#include "shell.h"

/**
 * get_shell_history_file - gets the shell history file
 * @info: parameter struct
 *
 * Return: allocated string containing the history file
 */
char *get_shell_history_file(shell_info_t *info)
{
	char *buffer, *directory;

	directory = get_environment_variable(info, "HOME=");
	if (!directory)
		return NULL;

	buffer = malloc(sizeof(char) * (string_length(directory) + string_length(HISTORY_FILE) + 2));
	if (!buffer)
		return NULL;

	buffer[0] = 0;
	string_copy(buffer, directory);
	string_concatenate(buffer, "/");
	string_concatenate(buffer, HISTORY_FILE);

	return buffer;
}

/**
 * write_shell_history - creates a file or appends to an existing file with shell history
 * @info: the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int write_shell_history(shell_info_t *info)
{
	ssize_t file_descriptor;
	char *filename = get_shell_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	file_descriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (file_descriptor == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		write_to_file_descriptor(node->str, file_descriptor);
		write_to_file_descriptor("\n", file_descriptor);
	}

	write_to_file_descriptor(FLUSH_BUFFER, file_descriptor);
	close(file_descriptor);

	return 1;
}

/**
 * read_shell_history - reads shell history from a file
 * @info: the parameter struct
 *
 * Return: history count on success, 0 otherwise
 */
int read_shell_history(shell_info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_stat;
	char *buffer = NULL, *filename = get_shell_history_file(info);

	if (!filename)
		return 0;

	file_descriptor = open(filename, O_RDONLY);
	free(filename);

	if (file_descriptor == -1)
		return 0;

	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;

	if (file_size < 2)
		return 0;

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return 0;

	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;

	if (read_length <= 0)
		return (free(buffer), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_shell_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_shell_history_list(info, buffer + last, line_count++);

	free(buffer);
	info->history_count = line_count;

	while (info->history_count-- >= MAX_HISTORY_COUNT)
		delete_node_at_index(&(info->history), 0);

	renumber_shell_history(info);

	return info->history_count;
}

/**
 * build_shell_history_list - adds an entry to the shell history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buffer: buffer
 * @line_count: the history line count
 *
 * Return: Always 0
 */
int build_shell_history_list(shell_info_t *info, char *buffer, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buffer, line_count);

	if (!info->history)
		info->history = node;

	return 0;
}

/**
 * renumber_shell_history - renumbers the shell history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new history count
 */
int renumber_shell_history(shell_info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return info->history_count = i;
}
