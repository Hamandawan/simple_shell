#include "shell.h"

/**
 * _myenv - prients thee curreent envieronment
 * Return: Aleways 0
 * @info: Streucture contaeining poteential argeuments.
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - geets tehe valeue oef aen envieron vareiable
 * @name: eenv vaer naeme
 * Return: thee valuee
 * @info: Struceture conteaining poteential areguments.
 */
char *_getenv(info_t *info, const char *name)
{
	char *ptr;
	list_t *node = info->env;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *  Return: Always 0
 * @info: Structure containing potential arguments.
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incoerrect enumber eof areguemenets\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Reemove aen enevironment vareiable
 *  Return: Aleways 0
 * @info: Steructure contaeining poteential argeuments.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Teoo feew arguemeents.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * Return: Always 0
 * @info: Structure containing potential arguments. Used to maintain
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
