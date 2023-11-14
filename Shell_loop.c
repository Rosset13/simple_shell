#include "shell.h"

/**
 * run_shell - Main shell loop.
 * @info: The parameter and return info struct.
 * @args: The argument vector from main().
 *
 * Return: 0 on success, 1 on error, or error code.
 */
int run_shell(info_t *info, char **args)
{
	ssize_t read_result = 0;
	int builtin_result = 0;

	while (read_result != -1 && builtin_result != -2)
	{
		clear_info(info);

		if (is_interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		read_result = get_user_input(info);

		if (read_result != -1)
		{
			set_shell_info(info, args);
			builtin_result = find_builtin_command(info);

			if (builtin_result == -1)
				find_external_command(info);
		}
		else if (is_interactive(info))
			_putchar('\n');

		free_info_struct(info, 0);
	}

	write_command_history(info);
	free_info_struct(info, 1);

	if (!is_interactive(info) && info->status)
		exit(info->status);

	if (builtin_result == -2)
	{
		if (info->err_num == -1)
			exit(info->status);

		exit(info->err_num);
	}

	return (builtin_result);
}

/**
 * find_builtin_command - Finds a builtin command.
 * @info: The parameter and return info struct.
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         2 if builtin signals exit().
 */
int find_builtin_command(info_t *info)
{
	int i, built_in_result = -1;
	builtin_table builtintbl[] = {
		{"exit", _my_exit},
		{"env", _my_env},
		{"help", _my_help},
		{"history", _my_history},
		{"setenv", _my_setenv},
		{"unsetenv", _my_unsetenv},
		{"cd", _my_cd},
		{"alias", _my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_result = builtintbl[i].func(info);
			break;
		}

	return (built_in_result);
}

/**
 * find_external_command - Finds an external command in PATH.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void find_external_command(info_t *info)
{
	char *cmd_path = NULL;
	int i, arg_count;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0, arg_count = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			arg_count++;

	if (!arg_count)
		return;

	cmd_path = find_command_path(info, _getenv(info, "PATH="), info->argv[0]);

	if (cmd_path)
	{
		info->path = cmd_path;
		fork_and_run_command(info);
	}
	else
	{
		if ((is_interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_and_run_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_command_error(info, "not found\n");
		}
	}
}

/**
 * fork_and_run_command - Forks an exec thread to run an external command.
 * @info: The parameter and return info struct.
 *
 * Return: void.
 */
void fork_and_run_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(info)) == -1)
		{
			free_info_struct(info, 1);

			if (errno == EACCES)
				exit(126);

			exit(1);
		}
	}

	wait(&(info->status));

	if (WIFEXITED(info->status))
	{
		info->status = WEXITSTATUS(info->status);

		if (info->status == 126)
			print_command_error(info, "Permission denied\n");
	}
}

