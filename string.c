#include "shell.h"

/**
 * string_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *str)
{
	int length = 0;

	if (!str)
		(return 0;)

	while (*str++)
		length++;
	(return length;)
}

/**
 * string_compare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		(return 0;)
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if haystack starts with needle
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			(return NULL;)
	(return (char *)haystack;)
}

/**
 * string_concat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_concat(char *dest, char *src)
{
	char *result = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	(return result;)
}
