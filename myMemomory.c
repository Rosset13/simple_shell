#include "shell.h"

/**
 * bfree - Frees a pointer and NULLs the address.
 * @ptr: Address of the pointer to free.
 *
 * Return: 1 if freed successfully, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
	{
		return (0); /* Nothing to free */
	}

	free(*ptr);
	*ptr = NULL;

	return (1); /* Freed successfully */
}

