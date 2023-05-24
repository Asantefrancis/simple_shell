#include "shell.h"

/**
 * my_strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *my_strcpy(char *dest, const char *src)
{
	int i = 0;

	if (dest == src || src == NULL)
		return dest;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return dest;
}

/**
 * my_strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return NULL;

	while (str[length] != '\0')
		length++;

	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return NULL;

	for (int i = 0; i <= length; i++)
		ret[i] = str[i];

	return ret;
}

/**
 * my_puts - prints a string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_puts(const char *str)
{
	if (str == NULL)
		return;

	for (int i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return 1;
}
