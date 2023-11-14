#include "shell.h"

/**
 * locate_command - Finds the executable command in the PATH string.
 * @information: The information struct.
 * @path_string: The PATH string.
 * @command: The command to locate.
 *
 * Return: Full path of the command if found, NULL otherwise.
 */
char *locate_command(info_t *information, char *path_string, char *command)
{
	int index = 0, current_position = 0;
	char *path_entry;

	if (!path_string || !command)
		return (NULL);

	/* Check if the command is a local executable */
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_executable(information, command))
			return (command);
	}

	while (path_string[index])
	{
		/* Find the next PATH entry */
		while (path_string[index] && path_string[index] != ':')
			index++;

		/* Extract the current PATH entry */
		path_entry = duplicate_chars(path_string, current_position, index);

		/* Append the command to the current PATH entry */
		concatenate_path(path_entry, "/", command);

		/* Check if the concatenated path is an executable command */
		if (is_executable(information, path_entry))
			return (path_entry);

		/* Move to the next position in PATH */
		if (path_string[index])
			index++;
		current_position = index;
	}

	return (NULL);
}

