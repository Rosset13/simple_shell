#include "shell.h"

/**
 * print_prompt - Prints the shell prompt
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		_puts("SimpleShell$ ");
}

/**
 * is_shell_variable - checks if a substring is a shell variable
 * @str: The string to check
 * @start: The starting position of the variable
 * @end: The ending position of the variable
 *
 * Return: 1 if the substring is a shell variable, 0 otherwise
 */
int is_shell_variable(char *str, size_t *start, size_t *end)
{
	size_t i = *start;

	if (str[i] == '$' && (str[i + 1] == '?' || _isalpha(str[i + 1])))
	{
		if (str[i + 1] == '?')
		{
			*start = i;
			*end = i + 1;
			return (1);
		}

		while (_isalpha(str[i + 1]) || str[i + 1] == '_')
			i++;

		*start = i - (*start);
		*end = i;
		return (1);
	}

	return (0);
}

/**
 * process_shell_variable - processes a shell variable in a string
 * @shell_info: Structure containing information about the shell
 * @str: The string to process
 * @start: The starting position of the variable
 * @end: The ending position of the variable
 * @i: Current index in the string
 *
 * Return: 1 if a shell variable was processed, 0 otherwise
 */
int process_shell_variable(info_t *shell_info, char *str, size_t *start, size_t *end, size_t i)
{
	char *variable = NULL;
	char *value = NULL;

	if (is_shell_variable(str, start, end))
	{
		variable = dup_chars(str, *start + 1, *end - *start);

		if (str[*end + 1] == '\0')
		{
			value = _getenv(shell_info, variable + 1);

			if (value)
			{
				free(variable);
				replace_string(&str, value);
				return (1);
			}

			free(variable);
			return (0);
		}

		while (_isalpha(str[i + 1]) || str[i + 1] == '_')
			i++;

		variable = dup_chars(str, *start + 1, i - *start);
		value = _getenv(shell_info, variable + 1);

		if (value)
		{
			free(variable);
			replace_string(&str, value);
			return (1);
		}

		free(variable);
	}

	return (0);
}

/**
 * replace_alias - replaces alias in a string with its value
 * @shell_info: Structure containing information about the shell
 *
 * Return: Always 0
 */
int replace_alias(info_t *shell_info)
{
	/* Placeholder for replacing aliases */
	return (0);
}

/**
 * replace_shell_variables - replaces shell variables in a string with their values
 * @shell_info: Structure containing information about the shell
 *
 * Return: Always 0
 */
int replace_shell_variables(info_t *shell_info)
{
	size_t start = 0, end = 0, i = 0;
	char *str = shell_info->arg;

	while (str[i])
	{
		if (process_shell_variable(shell_info, str, &start, &end, i))
			i = start + _strlen(_getenv(shell_info, str + start + 1)) - 1;
		i++;
	}

	return (0);
}
