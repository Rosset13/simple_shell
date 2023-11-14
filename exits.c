#include "shell.h"

/**
 * shs_strncpy - Copies a string.
 * @destination: The destination string to be copied to.
 * @source: The source string.
 * @max_length: The maximum number of characters to be copied.
 *
 * Return: A pointer to the destination string.
 */
char *shs_strncpy(char *destination, char *source, int max_length)
{
	int dest_index = 0, src_index = 0;
	char *result = destination;

	while (source[src_index] != '\0' && src_index < max_length - 1)
	{
		destination[dest_index] = source[src_index];
		dest_index++;
		src_index++;
	}

	/* Ensure null-termination */
	destination[dest_index] = '\0';

	return (result);
}

/**
 * shs_strncat - Concatenates two strings.
 * @destination: The first string.
 * @source: The second string.
 * @max_length: The maximum number of bytes to be used.
 *
 * Return: A pointer to the concatenated string.
 */
char *shs_strncat(char *destination, char *source, int max_length)
{
	int dest_index = 0, src_index = 0;
	char *result = destination;

	while (destination[dest_index] != '\0' && dest_index < max_length - 1)
		dest_index++;

	while (source[src_index] != '\0' && dest_index < max_length - 1)
	{
		destination[dest_index] = source[src_index];
		dest_index++;
		src_index++;
	}

	/* Ensure null-termination */
	destination[dest_index] = '\0';

	return (result);
}

/**
 * shs_strchr - Locates a character in a string.
 * @str: The string to be parsed.
 * @character: The character to look for.
 *
 * Return: A pointer to the first occurrence of the character in the string.
 */
char *shs_strchr(char *str, char character)
{
	do {
	
		if (*str == character)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

