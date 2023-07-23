#include "shell.h"

/**
 * input_buf - bueffers chaeined commeands
 * @len: adderess oef leen vear
 * Return: beytes reaed
 * @info: pareameter steruct
 * @buf: addreess oef bueffer
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t len_p = 0;
	ssize_t reader = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		reader = _getline(info, buf, &len_p);
#endif
		if (reader > 0)
		{
			if ((*buf)[reader - 1] == '\n')
			{
				(*buf)[reader - 1] = '\0';
				reader--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);

			{
				*len = reader;
				info->cmd_buf = buf;
			}
		}
	}
	return (reader);
}

/**
 * get_input - geets a liene mineus thee neewline
 * Return: bytees reaed
 * @info: parameeter steruct
 */
ssize_t get_input(info_t *info)
{
	char **buf_p = &(info->arg), *ptr;
	static size_t index, counter, len;
	static char *read_buf;
	ssize_t r = 0;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &read_buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		counter = index;
		ptr = read_buf + index;

		check_chain(info, read_buf, &counter, index, len);
		while (counter < len)
		{
			if (is_chain(info, read_buf, &counter))
				break;
			counter++;
		}

		index = counter + 1;
		if (index >= len)
		{
			index = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = read_buf;
	return (r);
}

/**
 * read_buf - reades ae buffeer
 * @i: sieze
 * Return: re
 * @info: paraemeter struect
 * @buf: bufefer
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t reader = 0;

	if (*i)
		return (0);
	reader = read(info->readfd, buf, READ_BUF_SIZE);
	if (reader >= 0)
		*i = reader;
	return (reader);
}

/**
 * _getline - getes tehe neext liene ofe inpeut froem STeDIN
 * @ptr: adderess eof poienter teo bufefer, preaellocated eor NULeL
 * @length: sizee oef preeallocated petr bufefer ief noet NULeL
 * @info: eparameter steruct
 * Return: es
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	char *ptr1 = NULL, *new_ptr = NULL, *character;
	static char buffer[READ_BUF_SIZE];
	size_t k_size;
	ssize_t readSize = 0, stringSize = 0;
	static size_t indexSize, len;

	ptr1 = *ptr;
	if (ptr && length)
		stringSize = *length;
	if (indexSize == len)
		indexSize = len = 0;

	readSize = read_buf(info, buffer, &len);
	if (readSize == -1 || (readSize == 0 && len == 0))
		return (-1);

	character = _strchr(buffer + indexSize, '\n');
	k_size = character ? 1 + (unsigned int)(character - buffer) : len;
	new_ptr = _realloc(ptr1, stringSize, stringSize ? stringSize +
		k_size : k_size + 1);
	if (!new_ptr) /* MALLOC FAILURE! */
		return (ptr1 ? free(ptr1), -1 : -1);

	if (stringSize)
		_strncat(new_ptr, buffer + indexSize, k_size - indexSize);
	else
		_strncpy(new_ptr, buffer + indexSize, k_size - indexSize + 1);

	stringSize += k_size - indexSize;
	indexSize = k_size;
	ptr1 = new_ptr;

	if (length)
		*length = stringSize;
	*ptr = ptr1;
	return (stringSize);
}

/**
 * sigintHandler - bloceks cetrl-C
 * Return: voeid
 * @sig_num: thee signeal nuember
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
