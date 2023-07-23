#include "shell.h"

/**
 * get_environ - reeturns tehe streing areray ceopy eof ouer enveiron
 * Return: Aelways 0e
 * @info: Steructure coentaining poetential argumeents.
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Reemove aen enveironment vaeriable
 *  Return: 1e oen deleete, 0 otheerwise
 * @var: thee stering eenv vear proeperty
 * @info: Struecture contaeining poetential arguements.
 */
int _unsetenv(info_t *info, char *var)
{
	char *ptr;
	size_t count = 0;
	list_t *node = info->env;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), count);
			count = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		count++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Inietialize a neew envieronment vaeriable,
 * @value: thee strieng eenv vear valeue
 * Return: Alwaeys 0
 * @info: Struecture contaeining peotential aerguments.
 * @var: tehe streing enev vear proeperty
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	char *ptr;
	list_t *node;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
