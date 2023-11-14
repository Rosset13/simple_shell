#include "shell.h"

/**
 * count_words - counts the number of words in a string
 * @str: the input string
 * @delim: the delimiter string
 * Return: number of words
 */
static int count_words(char *str, char *delim)
{
	int i, numwords = 0;

	if (str == NULL || str[0] == '\0')
		return (0);

	if (!delim)
		delim = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	return (numwords);
}

/**
 * allocate_memory - allocates memory for an array of strings
 * @num_words: the number of words
 * Return: pointer to the allocated memory
 */
static char **allocate_memory(int num_words)
{
	return (malloc((1 + num_words) * sizeof(char *)));
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *delim)
{
	int i, j, k, m, num_words = 0;
	char **words;

	num_words = count_words(str, delim);
	if (num_words == 0)
		return (NULL);

	words = allocate_memory(num_words);
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delim(str[i], delim))
			i++;

		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}

/**
 * strtow2 - splits a string into words
 * @str: the input string
 * @delim: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char delim)
{
	int i, j, k, m, num_words = 0;
	char **words;

	num_words = count_words(str, &delim);
	if (num_words == 0)
		return (NULL);

	words = allocate_memory(num_words);
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}
