#include "shell.h"

/**
 * display_history - Displays the history list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias identified by a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign_position;
	char temp_char;
	int result;

	equal_sign_position = _strchr(str, '=');
	if (!equal_sign_position)
		return (1);

	temp_char = *equal_sign_position;
	*equal_sign_position = 0;

	result = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));

	*equal_sign_position = temp_char;
	return (result);
}

/**
 * set_alias - Sets an alias to a string.
 * @info: Parameter struct.
 * @str: The string alias.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
	char *equal_sign_position;

	equal_sign_position = _strchr(str, '=');
	if (!equal_sign_position)
		return (1);

	if (!*++equal_sign_position)
		return (remove_alias(info, str));

	remove_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Prints an alias string.
 * @node: The alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
	char *equal_sign_position = NULL;
	char *alias_value = NULL;

	if (node)
	{
		equal_sign_position = _strchr(node->str, '=');

		for (alias_value = node->str; alias_value <= equal_sign_position; alias_value++)
			_putchar(*alias_value);

		_putchar('\'');
		_puts(equal_sign_position + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int manage_alias(info_t *info)
{
	int i = 0;
	char *equal_sign_position = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		equal_sign_position = _strchr(info->argv[i], '=');

		if (equal_sign_position)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
