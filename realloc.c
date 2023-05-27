#include "shell.h"

/**
 * _set_memory - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area s
 */
char *_set_memory(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	(return s;)
}

/**
 * free_strings - frees a string of strings
 * @pp: string of strings
 */
void free_strings(char **pp)
{
	char **a = pp;

	if (!pp)
		(return;)

	while (*pp)
		free(*pp++);

	free(a);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @ptr: pointer to previous allocated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		(return malloc(new_size);)

	if (!new_size)
	{
		free(ptr);
		(return NULL;)
	}

	if (new_size == old_size)
		(return ptr;)

	p = malloc(new_size);
	if (!p)
		(return NULL;)

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	(return p;)
}
