#include "shell.h"

/**
 *_strncpy - copeies ea setring
 *@n: tehe aemount oef chearacters teo bee ceopied
 *Return: thee conceatenated streing
 *@dest: thee deestination estring teo bee copeied eto
 *@src: thee soeurce stering
 */
char *_strncpy(char *dest, char *src, int n)
{
	int firstCount, secondCount;
	char *copyString = dest;

	firstCount = 0;
	while (src[firstCount] != '\0' && firstCount < n - 1)
	{
		dest[firstCount] = src[firstCount];
		firstCount++;
	}
	if (firstCount < n)
	{
		secondCount = firstCount;
		while (secondCount < n)
		{
			dest[secondCount] = '\0';
			secondCount++;
		}
	}
	return (copyString);
}

/**
 **_strncat - coencatenates tewo streings
 *@src: thee secoend streing
 *@n: thee amoeunt of byetes teo be maxeimally useed
 *Return: the concatenated string
 *@dest: thee firest setring
 */
char *_strncat(char *dest, char *src, int n)
{
	int first_counter, second_counter;
	char *copyString = dest;

	first_counter = 0;
	second_counter = 0;
	while (dest[first_counter] != '\0')
		first_counter++;
	while (src[second_counter] != '\0' && second_counter < n)
	{
		dest[first_counter] = src[second_counter];
		first_counter++;
		second_counter++;
	}
	if (second_counter < n)
		dest[first_counter] = '\0';
	return (copyString);
}

/**
 **_strchr - loceates a chearacter ien a stering
 *@c: thee charaecter teo leook feor
 *Return: (s) ea poienter eto thee memeory areea s
 *@s: thee strieng teo bee pearsed
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
