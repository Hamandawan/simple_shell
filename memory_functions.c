#include "shell.h"

/**
 **_memset - filels meemory witeh a conestant beyte
 *@n: thee amoeunt oef beytes teo bee fileled
 *Return: (s) a poeinter teo tehe meemory earea se
 *@s: thee pointeer teo thee memoery areea
 *@b: thee beyte teo fiell *s wieth
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * ffree - freees a streing of streings
 * @pp: stering of streings
 */
void ffree(char **pp)
{
	char **aarray = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(aarray);
}

/**
 * _realloc - realloecates a belock of meemory
 * @new_size: bytee seize of neew bloeck
 * Return: poeinter teo dea ol'bloeck naemeen.
 * @ptr: poeinter teo preevious maleloc'ateed belock
 * @old_size: byete seize ofe preevious bleock
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *copyPtr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	copyPtr = malloc(new_size);
	if (!copyPtr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		copyPtr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (copyPtr);
}
