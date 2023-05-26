#include "shell.h"

/**
 * getListLength - determines the length of a linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t getListLength(const list_t *h)
{
	size_t length = 0;

	while (h)
	{
		h = h->next;
		length++;
	}

	return length;
}

/**
 * listToStrings - returns an array of strings from the list's str field
 * @head: pointer to the first node
 *
 * Return: array of strings
 */
char **listToStrings(list_t *head)
{
	list_t *node = head;
	size_t length = getListLength(head);
	char **strings;
	char *str;
	size_t i, j;

	if (!head || !length)
		return NULL;

	strings = malloc(sizeof(char *) * (length + 1));
	if (!strings)
		return NULL;

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_stringLength(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return NULL;
		}

		str = _stringCopy(str, node->str);
		strings[i] = str;
	}

	strings[i] = NULL;
	return strings;
}


/**
 * printList - prints all elements of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of the list
 */
size_t printList(const list_t *h)
{
	size_t count = 0;

	while (h)
	{
		printNumber(convertNumber(h->num, 10, 0));
		printCharacter(':');
		printCharacter(' ');
		printString(h->str ? h->str : "(nil)");
		printString("\n");
		h = h->next;
		count++;
	}

	return count;
}

/**
 * findNodeWithPrefix - returns the node whose string starts with the prefix
 * @node: pointer to the list head
 * @prefix: string to match
 * @c: the next character after the prefix to match
 *
 * Return: matched node or NULL
 */
list_t *findNodeWithPrefix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = startsWith(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return node;
		node = node->next;
	}

	return NULL;
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to the list head
 * @node: pointer to the node
 *
 * Return: index of the node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
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
