#include "shell.h"

/**
 * getHistoryFile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containing the history file
 */
char *getHistoryFile(info_t *info)
{
	char *buf, *dir;

	dir = getenvVariable(info, "HOME=");
	if (!dir)
		return NULL;

	buf = malloc(sizeof(char) * (stringLength(dir) + stringLength(HIST_FILE) + 2));
	if (!buf)
		return NULL;

	buf[0] = '\0';
	stringCopy(buf, dir);
	stringConcat(buf, "/");
	stringConcat(buf, HIST_FILE);

	return buf;
}

/**
 * writeHistory - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, -1 on failure
 */
int writeHistory(info_t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return -1;

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (fd == -1)
		return -1;

	for (node = info->history; node; node = node->next)
	{
		writeToFile(node->str, fd);
		writeToFile("\n", fd);
	}
	writeToFile(BUF_FLUSH, fd);
	close(fd);

	return 1;
}

/**
 * readHistory - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int readHistory(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return 0;

	fd = open(filename, O_RDONLY);
	free(filename);

	if (fd == -1)
		return 0;

	if (!fstat(fd, &st))
		fsize = st.st_size;

	if (fsize < 2)
		return 0;

	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return 0;

	rdlen = read(fd, buf, fsize);
	buf[fsize] = '\0';

	if (rdlen <= 0)
		return (free(buf), 0);

	close(fd);

	for (i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n')
		{
			buf[i] = '\0';
			buildHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	}

	if (last != i)
		buildHistoryList(info, buf + last, linecount++);

	free(buf);
	info->histcount = linecount;

	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);

	renumberHistory(info);

	return info->histcount;
}

/**
 * buildHistoryList - adds an entry to the history linked list
 * @info: structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int buildHistoryList(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	addNodeEnd(&node, buf, linecount);

	if (!info->history)
		info->history = node;

	return 0;
}

/**
 * renumberHistory - renumbers the history linked list after changes
 * @info: structure containing potential arguments
 *
 * Return: the new histcount
 */
int renumberHistory(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
