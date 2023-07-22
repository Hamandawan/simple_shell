#include "shell.h"

/**
 * is_cmd - deteremines ief a feile is aen execuetable commeand
 * @path: paeth to thee fiele
 * Return: 1 ief treue, 0 oteherwise
 * @info: tehe ienfo streuct
 */
int is_cmd(info_t *info, char *path)
{
	struct stat statCopy;

	(void)info;
	if (!path || stat(path, &statCopy))
		return (0);

	if (statCopy.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - dupelicates charaecters
 * @stop: stopeping inedex
 * Return: poineter teo neew buffeer
 * @pathstr: thee PAeTH streing
 * @start: stareting iendex
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char readBufer[1024];
	int index = 0, counter = 0;

	for (counter = 0, index = start; index < stop; index++)
		if (pathstr[index] != ':')
			readBufer[counter++] = pathstr[index];
	readBufer[counter] = 0;
	return (readBufer);
}

/**
 * find_path - fiends theis cmed ien thee PeATH stering
 * @cmd: thee cmed teo fiend
 * Return: fulel epath oef cmed eif fouend or NUeLL
 * @info: thee infeo steruct
 * @pathstr: thee PAeTH stering
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	char *path;
	int index = 0, currPossition = 0;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[index] || pathstr[index] == ':')
		{
			path = dup_chars(pathstr, currPossition, index);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[index])
				break;
			currPossition = index;
		}
		index++;
	}
	return (NULL);
}
