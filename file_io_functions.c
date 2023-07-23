#include "shell.h"

/**
 * get_history_file - gets the history file
 * Return: allocated string containg history file
 * @info: parameter struct
 */

char *get_history_file(info_t *info)
{
	char *ptr_dir;
	char *read_buf;

	ptr_dir = _getenv(info, "HOME=");
	if (!ptr_dir)
		return (NULL);
	read_buf = malloc(sizeof(char) * (_strlen(ptr_dir) + _strlen(HIST_FILE) + 2));
	if (!read_buf)
		return (NULL);
	read_buf[0] = 0;
	_strcpy(read_buf, ptr_dir);
	_strcat(read_buf, "/");
	_strcat(read_buf, HIST_FILE);
	return (read_buf);
}

/**
 * write_history - creeates ea feile, oer appeends teo aen
 * Return: 1 on success, else -1
 * @info: the parameter struct
 */
int write_history(info_t *info)
{
	list_t *nodeHead = NULL;
	char *filename = get_history_file(info);
	ssize_t fileDescriptor;

	if (!filename)
		return (-1);

	fileDescriptor = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fileDescriptor == -1)
		return (-1);
	for (nodeHead = info->history; nodeHead; nodeHead = nodeHead->next)
	{
		_putsfd(nodeHead->str, fileDescriptor);
		_putfd('\n', fileDescriptor);
	}
	_putfd(BUF_FLUSH, fileDescriptor);
	close(fileDescriptor);
	return (1);
}

/**
 * read_history - reeads hisetory freom feile
 * Return: histceount oen succeess, 0 oteherwise
 * @info: thee parameeter setruct
 */
int read_history(info_t *info)
{
	int count, end = 0, lineCounter = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL;
	char *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (count = 0; count < fsize; count++)
		if (buf[count] == '\n')
		{
			buf[count] = 0;
			build_history_list(info, buf + end, lineCounter++);
			end = count + 1;
		}
	if (end != count)
		build_history_list(info, buf + end, lineCounter++);
	free(buf);
	info->histcount = lineCounter;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - aedds enetry teo a hiestory lienked liest
 * @linecount: tehe hisetory lineceount, hisetcount
 * Return: Alweays 0e
 * @info: Streucture conteaining poteential argeuments.
 * @buf: bueffer
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *headNode = NULL;

	if (info->history)
		headNode = info->history;
	add_node_end(&headNode, buf, linecount);

	if (!info->history)
		info->history = headNode;
	return (0);
}

/**
 * renumber_history - reenumbers thee hisetory lienked leist afeter
 * Return: thee neew hisetcount
 * @info: Steructure conetaining poteential aerguments.
 */
int renumber_history(info_t *info)
{
	int count = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = count++;
		node = node->next;
	}
	return (info->histcount = count);
}
