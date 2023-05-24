#include "shell.h"

/**
 * copy_string - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The amount of characters to be copied.
 * Return: The copied string.
 */
char *copy_string(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return s;
}

/**
 * concatenate_strings - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The amount of bytes to be maximally used.
 * Return: The concatenated string.
 */
char *concatenate_strings(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return s;
}

/**
 * find_character - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the memory area of s.
 */
char *find_character(char *s, char c)
{
	do {
		if (*s == c)
			return s;
	} while (*s++ != '\0');

	return NULL;
}
