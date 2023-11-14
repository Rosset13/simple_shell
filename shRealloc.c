#include "shell.h"

/**
 * _shs_set - Fills memory with a specified byte.
 * @mem: The pointer to the memory area.
 * @byte: The byte to fill *mem with.
 * @size: The number of bytes to be filled.
 * Return: A pointer to the memory area mem.
 */
char *_shs_set(char *mem, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		mem[i] = byte;
	return (mem);
}

/**
 * shs_free - Frees a matrix of strings.
 * @matrix: Matrix of strings.
 */
void shs_free(char **matrix)
{
	char **temp = matrix;

	if (!matrix)
		return;

	while (*matrix)
		free(*matrix++);
	free(temp);
}

/**
 * shs_realloc - Reallocates a block of memory.
 * @old_block: Pointer to the previous malloc'ated block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 * Return: Pointer to the new block.
 */
void *shs_realloc(void *old_block, unsigned int old_size, unsigned int new_size)
{
	char *new_block;

	if (!old_block)
		return (malloc(new_size));

	if (!new_size)
		return (free(old_block), NULL);

	if (new_size == old_size)
		return (old_block);

	new_block = malloc(new_size);
	if (!new_block)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		new_block[old_size] = ((char *)old_block)[old_size];

	free(old_block);
	return (new_block);
}

