/**
 * my_strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int my_strlen(const char *s)
{
	int length = 0;

	if (s == NULL)
		return 0;

	while (s[length] != '\0')
		length++;

	return length;
}

/**
 * my_strcmp - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int my_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}

	if (*s1 == *s2)
		return 0;
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if haystack starts with needle
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: pointer to the next character after needle in haystack or NULL
 */
const char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle != *haystack)
			return NULL;
		needle++;
		haystack++;
	}

	return haystack;
}

/**
 * my_strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *my_strcat(char *dest, const char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return ret;
}
