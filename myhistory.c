#include "shell.h"

/**
 * obtain_history_file - Gets the history file.
 * @info: Parameter structure.
 *
 * Return: Allocated string containing the history file.
 */
char *obtain_history_file(info_t *info)
{
	char *file_path, *home_directory;

	home_directory = _getenv(info, "HOME=");
	if (!home_directory)
		return (NULL);

	file_path = malloc(sizeof(char) * (_strlen(home_directory) + _strlen(HISTORY_FILE) + 2));
	if (!file_path)
		return (NULL);

	file_path[0] = '\0';
	_strcpy(file_path, home_directory);
	_strcat(file_path, "/");
	_strcat(file_path, HISTORY_FILE);

	return (file_path);
}

/**
 * write_to_history - Creates a file, or appends to an existing file.
 * @info: The parameter structure.
 *
 * Return: 1 on success, else -1.
 */
int write_to_history(info_t *info)
{
	ssize_t file_descriptor;
	char *file_name = obtain_history_file(info);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);

	if (file_descriptor == -1)
		return (-1);

	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 * read_from_history - Reads history from a file.
 * @info: The parameter structure.
 *
 * Return: Histcount on success, 0 otherwise.
 */
int read_from_history(info_t *info)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat status;
	char *buffer = NULL, *file_name = obtain_history_file(info);

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);

	if (file_descriptor == -1)
		return (0);

	if (!fstat(file_descriptor, &status))
		file_size = status.st_size;

	if (file_size < 2)
		return (0);

	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);

	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';

	if (read_length <= 0)
		return (free(buffer), 0);

	close(file_descriptor);

	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			build_history_list(info, buffer + last, line_count++);
			last = i + 1;
		}

	if (last != i)
		build_history_list(info, buffer + last, line_count++);

	free(buffer);
	info->histcount = line_count;

	while (info->histcount-- >= HISTORY_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);
	return (info->histcount);
}

/**
 * add_to_history_list - Adds an entry to a history linked list.
 * @info: Structure containing potential arguments.
 * @buf: Buffer.
 * @line_count: The history line count, histcount.
 *
 * Return: Always 0.
 */
int add_to_history_list(info_t *info, char *buf, int line_count)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;

	add_node_end(&node, buf, line_count);

	if (!info->history)
		info->history = node;

	return (0);
}

/**
 * renumber_history_list - Renumbers the history linked list after changes.
 * @info: Structure containing potential arguments.
 *
 * Return: The new histcount.
 */
int renumber_history_list(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}

