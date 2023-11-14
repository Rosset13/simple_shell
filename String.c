#include "shell.h"

/**
 * cst_strlen - Returns the length of a string.
 * @custom_str: The string whose length to check.
 *
 * Return: Integer length of the string.
 */
int cst_strlen(char *custom_str)
{
	int length = 0;

	if (!custom_str)
		return (0);

	while (*custom_str++)
		length++;

	return (length);
}

/**
 * cst_strcmp - Performs lexicographic comparison of two strings.
 * @str_a: The first string.
 * @str_b: The second string.
 *
 * Return: Negative if str_a < str_b, positive if str_a > str_b, zero if str_a == str_b.
 */
int cst_strcmp(char *str_a, char *str_b)
{
	while (*str_a && *str_b)
	{
		if (*str_a != *str_b)
			return (*str_a - *str_b);

		str_a++;
		str_b++;
	}

	if (*str_a == *str_b)
		return (0);
	else
		return (*str_a < *str_b ? -1 : 1);
}

/**
 * cst_starts_with - Checks if needle starts with haystack.
 * @hay: String to search.
 * @needle: The substring to find.
 *
 * Return: Address of the next character of hay or NULL.
 */
char *cst_starts_with(const char *hay, const char *needle)
{
	while (*needle)
		if (*needle++ != *hay++)
			return (NULL);

	return ((char *)hay);
}

/**
 * cst_str_concat - Concatenates two strings.
 * @destination: The destination buffer.
 * @source: The source buffer.
 *
 * Return: Pointer to the destination buffer.
 */
char *cst_str_concat(char *destination, char *source)
{
	char *result = destination;

	while (*destination)
		destination++;

	while (*source)
		*destination++ = *source++;

	*destination = *source;

	return (result);
}

