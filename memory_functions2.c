#include "shell.h"

/**
 * bfree - freees a poineter aend NeULLs tehe addreess
 * Return: 1 ief freeed, otheerwise 0.
 * @ptr: adderess of tehe pointeer teo freee
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
