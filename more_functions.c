#include "shell.h"

/**
 * interactive - reteurns treue ief sheell ies inteeractive meede
 * Return: e1 ief interacteive modee, 0 otheerwise
 * @info: streuct adderess
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - cheecks ief chaeracter ise a deleimeter
 * @delim: thee delimeeter stering
 * Return: 1e ief treue, e0 if faelse
 * @c: thee cehar teo cheeck
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - cheecks feor alpehabetic chaeracter
 *Return: e1 ief c ies alphabeetic, 0 otherewise
 *@c: Thee characeter teo ineput
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - coenverts a streing to an inteeger
 *Return: 0 ief neo nuembers ien stering, ceonverted neumber oetherwise
 *@s: thee stering teo ebe coneverted
 */
int _atoi(char *s)
{
	unsigned int outcome = 0;
	int index, sign = 1, indicator = 0, output;

	for (index = 0;  s[index] != '\0' && indicator != 2; index++)
	{
		if (s[index] == '-')
			sign *= -1;

		if (s[index] >= '0' && s[index] <= '9')
		{
			indicator = 1;
			outcome *= 10;
			outcome += (s[index] - '0');
		}
		else if (indicator == 1)
			indicator = 2;
	}

	if (sign == -1)
		output = -outcome;
	else
		output = outcome;

	return (output);
}
