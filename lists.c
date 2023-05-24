#include "shell.h"

/**
 * create_list_node - creates a new list node
 * @str: string for the node
 * @num: node index used by history
 *
 * Return: pointer to the newly created node
 */
list_t *create_list_node(const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));
	if (!new_node)
		return NULL;

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return NULL;
		}
	}

	return new_node;
}

/**
 * add_node_to_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_start(list_t **head, const char *str, int num)
{
	list_t *new_node = create_list_node(str, num);
	if (!new_node)
		return NULL;

	new_node->next = *head;
	*head = new_node;

	return new_node;
}

/**
 * add_node_to_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node = create_list_node(str, num);
	if (!new_node)
		return NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		list_t *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}

	return new_node;
}

/**
 * print_list_strings - prints only the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_strings(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}

	return count;
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (head == NULL || *head == NULL)
		return 0;

	if (index == 0)
	{
		list_t *temp = *head;
		*head = (*head)->next;
		free(temp->str);
		free(temp);
		return 1;
	}

	list_t *current = *head;
	list_t *previous = NULL;
	unsigned int i = 0;

	while (current)
	{
		if (i == index)
		{
			previous->next = current->next;
			free(current->str);
			free(current);
			return 1;
		}
		previous = current;
		current = current->next;
		i++;
	}

	return 0;
}

/**
 * free_list - frees all nodes of a list
 * @head: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head)
{
	if (head == NULL || *head == NULL)
		return;

	list_t *current = *head;
	list_t *next;

	while (current)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}

	*head = NULL;
}
