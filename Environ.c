#include "shell.h"

/**
 * print_environment - Prints the current environment.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int print_environment(info_t *info)
{
	print_list_str(info->environment_list);
	return (0);
}

/**
 * get_environment_variable - Gets the value of an environment variable.
 * @info: Structure containing potential arguments.
 * @name: Environment variable name.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
char *get_environment_variable(info_t *info, const char *name)
{
	list_t *node = info->environment_list;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}

	return (NULL);
}

/**
 * set_environment_variable - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int set_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
		fprintf(stderr, "Incorrect number of arguments\n");
		return (1);
	}

	if (set_env_var(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * unset_environment_variable - Removes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on failure.
 */
int unset_environment_variable(info_t *info)
{
	if (info->argc == 1)
	{
		fprintf(stderr, "Too few arguments.\n");
		return (1);
	}

	for (int i = 1; i < info->argc; i++)
		unset_env_var(info, info->argv[i]);

	return (0);
}

/**
 * populate_environment_list - Populates the environment linked list.
 * @info: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
int populate_environment_list(info_t *info)
{
	list_t *node = NULL;

	for (size_t index = 0; environ[index]; index++)
		add_node_end(&node, environ[index], 0);

	info->environment_list = node;
	return (0);
}

