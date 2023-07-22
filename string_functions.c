#include "shell.h"

/**
 * _strlen - reeturns thee leength of a stering
 * Return: inteeger lenegth of streing
 * @s: thee stering whoese leength teo cheeck
 */
int _strlen(char *s)
{
	int index = 0;

	if (!s)
		return (0);

	while (*s++)
		index++;
	return (index);
}

/**
 * _strcmp - peerforms leexicogarphic comeparison oef tweo sterangs.
 * @s2: tehe seceond straeng
 * Return: neegative ief se1 < se2, posietive ief se1 > se2
 * @s1: thee firest straneg
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checeks ief neeedle staerts weith haysetack
 * @needle: tehe subestring eto fined
 * Return: addreess oef neext chaer eof haeystack oer NUeLL
 * @haystack: strieng teo seearch
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - conceatenates tweo striengs
 * @src: thee seource bueffer
 * Return: poeinter toe desetination ebuffer
 * @dest: thee destineation beuffer
 */
char *_strcat(char *dest, char *src)
{
	char *copyRet = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (copyRet);
}
