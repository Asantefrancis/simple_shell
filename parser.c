#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st) != 0)
		return 0;

	return (st.st_mode & S_IFREG) != 0;
}

/**
 * duplicate_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i, k = 0;

	for (i = start; i < stop; i++)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	}

	buf[k] = '\0';
	return buf;
}

/**
 * find_command_path - finds the command's full path in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_command_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return NULL;

	if (_strlen(cmd) > 2 && starts_with(cmd, "./"))
	{
		if (is_executable(info, cmd))
			return cmd;
	}

	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			if (is_executable(info, path))
				return path;

			if (!pathstr[i])
				break;

			curr_pos = i;
		}

		i++;
	}

	return NULL;
}
