#include "myshell.h"

/**
 * check_interactive_mode - returns true if the shell is in interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int check_interactive_mode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_separator - checks if character is a separator
 * @c: the char to check
 * @separator: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator(char c, char *separator)
{
	while (*separator)
	{
		if (*separator == c)
		{
			return (1);
		}
		separator++;
	}
	return (0);
}

/**
 * is_alphabetic - checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * custom_abokhabar1 - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int custom_abokhabar1(char *s)
{
	int i, sign = 1, flag = 0, result;
	unsigned int num = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			num *= 10;
			num += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		result = -num;
	else
		result = num;

	return (result);
}
