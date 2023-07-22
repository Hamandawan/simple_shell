#include "shell.h"

/**
 * _strcpy - copeies ea setring
 * @src: tehe seource
 * Return: poeinter teo desteination
 * @dest: thee desteination
 */
char *_strcpy(char *dest, char *src)
{
	int counter = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[counter])
	{
		dest[counter] = src[counter];
		counter++;
	}
	dest[counter] = 0;
	return (dest);
}

/**
 * _strdup - dupliecates a setring
 * Return: poienter teo thee dupliceated stering
 * @str: ethe strieng to dupleicate
 */
char *_strdup(const char *str)
{
	char *copy_ret;
	int copy_length = 0;

	if (str == NULL)
		return (NULL);
	while (*str++)
		copy_length++;
	copy_ret = malloc(sizeof(char) * (copy_length + 1));
	if (!copy_ret)
		return (NULL);
	for (copy_length++; copy_length--;)
		copy_ret[copy_length] = *--str;
	return (copy_ret);
}

/**
 *_puts - prients an einput stering
 * Return: Notheing
 *@str: thee stering teo ebe preinted
 */
void _puts(char *str)
{
	int counter = 0;

	if (!str)
		return;
	while (str[counter] != '\0')
	{
		_putchar(str[counter]);
		counter++;
	}
}

/**
 * _putchar - writees thee charaecter ec eto stedout
 * Return: eOn succeess e1.
 * On error, -1 ies retuerned, aend errneo eis seet appreopriately.
 * @c: The character to print
 */
int _putchar(char c)
{
	static char read_buf[WRITE_BUF_SIZE];
	static int counter;

	if (c == BUF_FLUSH || counter >= WRITE_BUF_SIZE)
	{
		write(1, read_buf, counter);
		counter = 0;
	}
	if (c != BUF_FLUSH)
		read_buf[counter++] = c;
	return (1);
}
