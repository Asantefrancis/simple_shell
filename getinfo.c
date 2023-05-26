#include "shell.h"

/**
 * initializeInfo - initializes info_t struct
 * @info: struct address
 */
void initializeInfo(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setInfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setInfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicateString(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replaceVariables(info);
	}
}

/**
 * freeInfo - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void freeInfo(info_t *info, int all)
{
	freeStringArray(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLinkedList(&(info->env));
		if (info->history)
			freeLinkedList(&(info->history));
		if (info->alias)
			freeLinkedList(&(info->alias));
		freeStringArray(info->environ);
		info->environ = NULL;
		freeBuffer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		printCharacter(BUF_FLUSH);
	}
}
