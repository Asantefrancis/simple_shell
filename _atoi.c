#include "shell.h"

/**
 * checkInteractiveMode - checks if the shell is running in interactive mode
 * @info: pointer to info_t struct
 *
 * Return: 1 if running in interactive mode, 0 otherwise
 */
int checkInteractiveMode(info_t *info)
{
    return (isInputTerminal() && info->readfd <= 2);
}

/**
 * isDelimiter - checks if a character is a delimiter
 * @c: character to check
 * @delim: delimiter string
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int isDelimiter(char c, char *delim)
{
    while (*delim)
    {
        if (*delim++ == c)
            return (1);
    }
    return (0);
}

/**
 * isAlphabetic - checks if a character is alphabetic
 * @c: character to check
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int isAlphabetic(int c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return (1);
    else
        return (0);
}

/**
 * convertToInt - converts a string to an integer
 * @s: string to convert
 *
 * Return: 0 if there are no numbers in the string, the converted number otherwise
 */
int convertToInt(char *s)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
            flag = 2;
    }

    if (sign == -1)
        output = -result;
    else
        output = result;

    return (output);
}
