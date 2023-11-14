#include "shell.h"

/**
 * sh_puts - Prints an input string to stderr.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */
void sh_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		sh_putchar(str[index]);
		index++;
	}
}

/**
 * sh_putchar - Writes the character c to stderr.
 * @c: The character to print.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int sh_putchar(char c)
{
	static int buffer_index;
	static char output_buffer[SHELL_WRITE_BUF_SIZE];

	if (c == SHELL_BUF_FLUSH || buffer_index >= SHELL_WRITE_BUF_SIZE)
	{
		if (write_to_file_descriptor(2, output_buffer, buffer_index) == -1)
			return (-1);
		buffer_index = 0;
	}
	if (c != SHELL_BUF_FLUSH)
		output_buffer[buffer_index++] = c;
	return (1);
}

/**
 * sh_putfd - Writes the character c to the given fd.
 * @c: The character to print.
 * @fd: The file descriptor to write to.
 *
 * Return: On success, 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int sh_putfd(char c, int fd)
{
	static int buffer_index;
	static char output_buffer[SHELL_WRITE_BUF_SIZE];

	if (c == SHELL_BUF_FLUSH || buffer_index >= SHELL_WRITE_BUF_SIZE)
	{
		if (write_to_file_descriptor(fd, output_buffer, buffer_index) == -1)
			return (-1);
		buffer_index = 0;
	}
	if (c != SHELL_BUF_FLUSH)
		output_buffer[buffer_index++] = c;
	return (1);
}

/**
 * sh_putsfd - Prints an input string to the specified file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int sh_putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += sh_putfd(*str++, fd);
	}
	return (count);
}

/**
 * write_to_file_descriptor - Helper function to write a buffer to a file descriptor.
 * @fd: The file descriptor to write to.
 * @buf: The buffer containing data to be written.
 * @size: The size of the buffer.
 *
 * Return: On success, the number of bytes written. On error, -1 is returned.
 */
ssize_t write_to_file_descriptor(int fd, char *buf, size_t size)
{
	return write(fd, buf, size);
}

