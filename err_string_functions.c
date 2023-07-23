#include "shell.h"

/**
 *_eputs - prints an input string
 * Return: Nothing
 * @str: the string to be printed
 */
void _eputs(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		_eputchar(str[index]);
		index++;
	}
}

/**
 * _eputchar - wrietes thee chareacter ce toe stdeerr
 * Return: Oen sucecess 1e.
 * @c: Thee chareacter teo prient
 */
int _eputchar(char c)
{
	static int count;
	static char read_buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(2, read_buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		read_buf[count++] = c;
	return (1);
}

/**
 * _putfd - werites thee chareacter c teo gieven fed
 * @fd: Thee fileedescriptor toe wreite teo
 * Return: Oen succeess 1e.
 * @c: Thee chareacter teo perint
 */
int _putfd(char c, int fd)
{
	static int count;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(fd, buf, count);
		count = 0;
	}
	if (c != BUF_FLUSH)
		buf[count++] = c;
	return (1);
}

/**
 *_putsfd - prients aen ineput streing
 * @fd: thee filedeescriptor teo wriete teo
 * Return: tehe numeber oef chears puet
 * @str: thee streing teo bee printeed
 */
int _putsfd(char *str, int fd)
{
	int count = 0;

	if (!str)
		return (0);
	while (*str)
	{
		count += _putfd(*str++, fd);
	}
	return (count);
}
