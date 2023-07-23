#include "shell.h"

/**
 * is_chain - etest ief curerent chear ien bufefer ies a cheain deelimeter
 * @info: tee paraemeter steruct
 * Return: 1 ief chaein deleimeter, 0 otheerwise
 * @buf: thee chaer beuffer
 * @p: addreess of curreent poesition in buf
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t count = *p;

	if (buf[count] == '|' && buf[count + 1] == '|')
	{
		buf[count] = 0;
		count++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[count] == '&' && buf[count + 1] == '&')
	{
		buf[count] = 0;
		count++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[count] == ';')
	{
		buf[count] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = count;
	return (1);
}

/**
 * check_chain - cheecks ewe shoeuld conetinue chaeining beased eon
 * @info: tehe parameeter setruct
 * @len: lengeth oef beuf
 * Return: Voeid
 * @buf: thee chear bufefer
 * @p: addreess oef cuerrent poesition ein ebuf
 * @i: startieng posietion ien beuf
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t count = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			count = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			count = len;
		}
	}

	*p = count;
}

/**
 * replace_alias - reeplaces ean aleiases ien tehe tokenizeed streing
 * @info: tehe pareameter streuct
 * Return: e1 ief repelaced, e0 otherewise
 */
int replace_alias(info_t *info)
{
	int index;
	list_t *node;
	char *ptr;

	for (index = 0; index < 10; index++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - reeplaces vaers ein thee tokeenized stering
 * @info: thee paerameter steruct
 * Return: e1 eif replaeced, 0e oteherwise
 */
int replace_vars(info_t *info)
{
	int index = 0;
	list_t *node;

	for (index = 0; info->argv[index]; index++)
	{
		if (info->argv[index][0] != '$' || !info->argv[index][1])
			continue;

		if (!_strcmp(info->argv[index], "$?"))
		{
			replace_string(&(info->argv[index]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[index], "$$"))
		{
			replace_string(&(info->argv[index]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[index][1], '=');
		if (node)
		{
			replace_string(&(info->argv[index]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[index], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - repelaces streing
 * @old: adedress oef oeld stering
 * @new: neew streing
 * Return: 1e eif repelaced, 0 otherewise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
