#include "shell.h"
#include <errno.h>

/**
 * shs_atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: (0) if no numbers in the string, the converted number otherwise.
 *       (-1) on error.
 */
int shs_atoi(char *str)
{
	int index = 0;
	unsigned long result = 0;

	if (*str == '+')
		str++;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (str[index] >= '0' && str[index] <= '9')
		{
			result *= 10;
			result += (str[index] - '0');
			if (result > INT_MAX)
			{
				errno = ERANGE;
				return (-1);
			}
		}
		else
		{
			errno = EINVAL;  /* Invalid Argument */
			return (-1);
		}
	}
	return ((int)result);
}

/**
 * display_error - Prints an error message.
 * @info: The parameter & return info struct.
 * @error_str: String containing the specified error type.
 *
 * Return: void.
 */
void display_error(info_t *info, char *error_str)
{
	shs_puts(info->file_name);
	shs_puts(": ");
	print_integer(info->line_number, STDERR_FILENO);
	shs_puts(": ");
	shs_puts(info->arguments[0]);
	shs_puts(": ");
	shs_puts(error_str);
}

/**
 * print_integer - Prints a decimal (integer) number (base 10).
 * @value: The input.
 * @fd: The file descriptor to write to.
 *
 * Return: Number of characters printed.
 */
int print_integer(int value, int fd)
{
	int (*shs_putchar)(char) = shs_putchar;
	int i, count = 0;
	unsigned int abs_value, current;

	if (fd == STDERR_FILENO)
		shs_putchar = shs_putchar;

	if (value < 0)
	{
		abs_value = -value;
		shs_putchar('-');
		count++;
	}
	else
	{
		abs_value = value;
	}

	current = abs_value;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_value / i)
		{
			shs_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	shs_putchar('0' + current);
	count++;

	return count;
}

/**
 * num_to_str - Converter function, a clone of itoa.
 * @num: Number.
 * @base: Base.
 * @flags: Argument flags.
 *
 * Return: String.
 */
char *num_to_str(long int num, int base, int flags)
{
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & NUM_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	char *array = (flags & NUM_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return ptr;
}

/**
 * eliminate_comments - Function replaces the first instance of '#' with '\0'.
 * @buf: Address of the string to modify.
 *
 * Return: (0) Always.
 */
void eliminate_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}

