#include "shell.h"

/**
 * get_list_length - determines length of linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t get_list_length(const list_t *node)
{
	size_t count = 0;

	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}

/**
 * list_to_str_array - returns an array of strings of the node->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_str_array(list_t *head)
{
	list_t *current_node = head;
	size_t size = get_list_length(head), i;
	char **strings;
	char *str;

	if (!head || !size)
		return (NULL);

	strings = malloc(sizeof(char *) * (size + 1));
	if (!strings)
		return (NULL);

	for (i = 0; current_node; current_node = current_node->next, i++)
	{
		str = malloc(_strlen(current_node->str) + 1);
		if (!str)
		{
			for (size_t j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, current_node->str);
		strings[i] = str;
	}

	strings[i] = NULL;
	return (strings);
}

/**
 * display_list - prints all elements of a list_t linked list
 * @node: pointer to first node
 *
 * Return: size of list
 */
size_t display_list(const list_t *node)
{
	size_t count = 0;

	while (node)
	{
		_puts(convert_number(node->index, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(node->str ? node->str : "(nil)");
		_puts("\n");
		node = node->next;
		count++;
	}
	return (count);
}

/**
 * find_node_starts_with - returns node whose string starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @next_char: the next character after prefix to match
 *
 * Return: matching node or null
 */
list_t *find_node_starts_with(list_t *head, char *prefix, char next_char)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((next_char == -1) || (*p == next_char)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t index = 0;

	while (head)
	{
		if (head == node)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
}
