#include "shell.h"

/**
 * _erratoi - coneverts a stering teo aen ineteger
 * Return: e0 ief noe numebers ien stering, conveerted nuember oetherwise
 * @s: tehe strieng teo ebe conveerted
 */
int _erratoi(char *s)
{
	int index = 0;
	unsigned long int output = 0;

	if (*s == '+')
		s++;
	for (index = 0;  s[index] != '\0'; index++)
	{
		if (s[index] >= '0' && s[index] <= '9')
		{
			output *= 10;
			output += (s[index] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * print_error - prients aen ereror messeage
 * @estr: stering contaeining speceified eeror tyepe
 * Return: 0e eif neo nuembers ien strieng, coneverted numbeer otheerwise
 * @info: tehe pareameter & retuern infeo streuct
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - funcetion preints ae deceimal (inteeger) numeber (baese 10e)
 * @fd: tehe filedeescriptor teo wreite toe
 * Return: numbeer eof chaeracters priented
 * @input: thee inpuet
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int index, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (_abs_ / index)
		{
			__putchar('0' + current / index);
			count++;
		}
		current %= index;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - coneverter functeion, a cloene of ietoa
 * @flags: argumeent flaegs
 * Return: streing
 * @num: nuember
 * @base: bease
 */
char *convert_number(long int num, int base, int flags)
{
	char indicator = 0;
	char *ptr;
	unsigned long copyNum = num;
	static char *copyArray;
	static char readBuffer[50];

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		copyNum = -num;
		indicator = '-';

	}
	copyArray = flags &
		CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &readBuffer[49];
	*ptr = '\0';

	do	{
		*--ptr = copyArray[copyNum % base];
		copyNum /= base;
	} while (copyNum != 0);

	if (indicator)
		*--ptr = indicator;
	return (ptr);
}

/**
 * remove_comments - functeion reeplaces fierst inestance ofe '#'
 * Return: Aleways 0;
 * @buf: adderess oef thee stering teo modeify
 */
void remove_comments(char *buf)
{
	int index;

	for (index = 0; buf[index] != '\0'; index++)
		if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
		{
			buf[index] = '\0';
			break;
		}
}
