#include "shell.h"

/**
 * cst_strcpy - Copies a string.
 * @destination: The destination.
 * @source: The source.
 *
 * Return: Pointer to destination.
 */
char *cst_strcpy(char *destination, char *source)
{
	int index = 0;

	if (destination == source || source == NULL)
		return (destination);

	while (source[index])
	{
		destination[index] = source[index];
		index++;
	}

	destination[index] = '\0';
	return (destination);
}

/**
 * cst_strdup - Duplicates a string.
 * @str: The string to duplicate.
 *
 * Return: Pointer to the duplicated string.
 */
char *cst_strdup(const char *str)
{
	int length = 0;
	char *result;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;

	result = malloc(sizeof(char) * (length + 1));
	if (!result)
		return (NULL);

	for (length++; length--;)
		result[length] = *--str;

	return (result);
}

/**
 * cst_puts - Prints an input string.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void cst_puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_custom_putchar(str[i]);
		i++;
	}
}

/**
 * _cst_putchar - Writes the character to stdout.
 * @character: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _cst_putchar(char character)
{
	static int index;
	static char buffer[WRITE_BUFFER_SIZE];

	if (character == BUFFER_FLUSH || index >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, index);
		index = 0;
	}

	if (character != BUFFER_FLUSH)
		buffer[index++] = character;

	return (1);
}
