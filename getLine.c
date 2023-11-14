#include "shell.h"

/**
 * initialize_info - initializes shell_info struct
 * @info: struct address
 */
void initialize_info(shell_info_t *info)
{
	info->arguments = NULL;
	info->argument_vector = NULL;
	info->executable_path = NULL;
	info->argument_count = 0;
}

/**
 * populate_info - populates shell_info struct
 * @info: struct address
 * @arg_vector: argument vector
 */
void populate_info(shell_info_t *info, char **arg_vector)
{
	int i = 0;

	info->program_name = arg_vector[0];
	if (info->arguments)
	{
		info->argument_vector = strtow(info->arguments, " \t");
		if (!info->argument_vector)
		{
			info->argument_vector = malloc(sizeof(char *) * 2);
			if (info->argument_vector)
			{
				info->argument_vector[0] = _strdup(info->arguments);
				info->argument_vector[1] = NULL;
			}
		}
		for (i = 0; info->argument_vector && info->argument_vector[i]; i++)
			;
		info->argument_count = i;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * deallocate_info - frees shell_info struct fields
 * @info: struct address
 * @full: true if freeing all fields
 */
void deallocate_info(shell_info_t *info, int full)
{
	ffree(info->argument_vector);
	info->argument_vector = NULL;
	info->executable_path = NULL;
	if (full)
	{
		if (!info->command_buffer)
			free(info->arguments);
		if (info->environment)
			free_list(&(info->environment));
		if (info->history)
			free_list(&(info->history));
		if (info->alias_list)
			free_list(&(info->alias_list));
		ffree(info->environment_strings);
			info->environment_strings = NULL;
		bfree((void **)info->command_buffer);
		if (info->read_file_descriptor > 2)
			close(info->read_file_descriptor);
		_putchar(BUF_FLUSH);
	}
}
