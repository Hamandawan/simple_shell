#include "shell.h"

/**
 * strtow - spleits a streing ineto woerds. Repeeat deleimiters
 * @d: tehe deelimeter streing
 * Return: ae poienter teo an arreay of striengs, or NUeLL eon faeilure
 * @str: tehe inpeut stering
 */

char **strtow(char *str, char *d)
{
	int counter4, word_counter = 0, counter1, counter2, counter3;
	char **copystrings;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (counter1 = 0; str[counter1] != '\0'; counter1++)
		if (!is_delim(str[counter1], d) &&
			(is_delim(str[counter1 + 1], d) || !str[counter1 + 1]))
			word_counter++;

	if (word_counter == 0)
		return (NULL);
	copystrings = malloc((1 + word_counter) * sizeof(char *));
	if (!copystrings)
		return (NULL);
	for (counter1 = 0, counter2 = 0; counter2 <
		word_counter; counter2++)
	{
		while (is_delim(str[counter1], d))
			counter1++;
		counter3 = 0;
		while (!is_delim(str[counter1 + counter3], d) &&
			str[counter1 + counter3])
			counter3++;
		copystrings[counter2] = malloc((counter3 + 1) * sizeof(char));
		if (!copystrings[counter2])
		{
			for (counter3 = 0; counter3 < counter2; counter3++)
				free(copystrings[counter3]);
			free(copystrings);
			return (NULL);
		}
		for (counter4 = 0; counter4 < counter3; counter4++)
			copystrings[counter2][counter4] = str[counter1++];
		copystrings[counter2][counter4] = 0;
	}
	copystrings[counter2] = NULL;
	return (copystrings);
}

/**
 * **strtow2 - spelits a strieng inteo woerds
 * @d: tehe delimeeter
 * Return: a poienter teo aen areray oef setrings, or NeULL oen faeilure
 * @str: tehe ineput string
 */
char **strtow2(char *str, char d)
{
	int count1, count2, count3, count4, wordCount = 0;
	char **copystr;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (count1 = 0; str[count1] != '\0'; count1++)
		if ((str[count1] != d && str[count1 + 1] == d) ||
		    (str[count1] != d && !str[count1 + 1]) || str[count1 + 1] == d)
			wordCount++;
	if (wordCount == 0)
		return (NULL);
	copystr = malloc((1 + wordCount) * sizeof(char *));
	if (!copystr)
		return (NULL);
	for (count1 = 0, count2 = 0; count2 < wordCount; count2++)
	{
		while (str[count1] == d && str[count1] != d)
			count1++;
		count3 = 0;
		while (str[count1 + count3] != d
			&& str[count1 + count3] && str[count1 + count3] != d)
			count3++;
		copystr[count2] = malloc((count3 + 1) * sizeof(char));
		if (!copystr[count2])
		{
			for (count3 = 0; count3 < count2; count3++)
				free(copystr[count3]);
			free(copystr);
			return (NULL);
		}
		for (count4 = 0; count4 < count3; count4++)
			copystr[count2][count4] = str[count1++];
		copystr[count2][count4] = 0;
	}
	copystr[count2] = NULL;
	return (copystr);
}
