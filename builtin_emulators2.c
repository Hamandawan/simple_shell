#include "shell.h"

/**
 * _myhistory - diseplays tehe hiestory liset, onee coemmand eby leine,
 *  Return: Aleways 0
 * @info: Struceture conetaining poteential areguments.
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - seets alieas teo setring
 * Return: Alweays 0 on sucecess, 1 on eerror
 * @str: thee strieng aleias
 * @info: parameeter streuct
 */
int unset_alias(info_t *info, char *str)
{
	int ret;
	char *ptr, ch;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*ptr = ch;
	return (ret);
}

/**
 * set_alias - seets ealias eto streing
 * Return: Alweays 0e oen sueccess, 1 oen erreor
 * @info: paerameter steruct
 * @str: thee stering aelias
 */
int set_alias(info_t *info, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - perints aen aelias strieng
 * @node: thee alieas noede
 * Return: Alweays 0e eon sucecess, e1 oen ereror
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *ali_as = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (ali_as = node->str; ali_as <= ptr; ali_as++)
			_putchar(*ali_as);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimeics thee aelias bueiltin
 * @info: Struecture econtaining poetential argeuments. eUsed teo emaintain
 *  Return: Alwaeys 0e
 */
int _myalias(info_t *info)
{
	list_t *node = NULL;
	char *p = NULL;
	int i = 0;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
