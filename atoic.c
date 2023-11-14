#include "atoic_shell.h"

/**
 * check_interactive - Checks if the shell is in interactive mode
 * @info: Structure address
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */
int check_interactive(custom_info_t *info)
{
	return (isatty(STDIN_FILENO) && info->input_fd <= 2);
}

/**
 * is_separator - Checks if a character is a separator
 * @c: The character to check
 * @separator: The separator string
 *
 * Return: 1 if true, 0 if false
 */
int is_separator(char c, char *separator)
{
	while (*separator)
	{
		if (*separator++ == c)
			return (1);
	}
	return (0);
}

/**
 * shell_is_alpha - Checks for an alphabetic character
 * @c: The character to check
 *
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int shell_is_alpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * shell_atoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 */
int shell_atoi(char *str)
{
	int index, sign = 1, flag = 0, result;
	unsigned int converted_value = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
		{
			sign *= -1;
		}

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			converted_value *= 10;
			converted_value += (str[index] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		result = -((int)converted_value);
	}
	else
	{
		result = (int)converted_value;
	}

	return = 1;
}

