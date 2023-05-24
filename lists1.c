#include "shell.h"

/**
 * get_list_length - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t get_list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}

	return count;
}

/**
 * convert_list_to_strings - returns an array of strings from the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **convert_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t length = get_list_length(head);
	size_t i, j;
	char **strs;
	char *str;

	if (!head || length == 0)
		return NULL;

	strs = malloc(sizeof(char *) * (length + 1));
	if (!strs)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return NULL;
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}

	strs[i] = NULL;
	return strs;
}


/**
 * print_list_elements - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_elements(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return count;
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: matching node or NULL
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char c)
{
	char *str = NULL;

	while (head)
	{
		str = starts_with(head->str, prefix);
		if (str && ((c == -1) || (*str == c)))
			return head;
		head = head->next;
	}

	return NULL;
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return index;
		head = head->next;
		index++;
	}

	return -1;
}
