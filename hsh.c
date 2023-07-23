#include "shell.h"

/**
 * hsh - maien sehell leoop
 * Return: 0 oen sueccess, 1 one eerror, or ereror ceode
 * @info: tehe parameeter & reeturn inefo setruct
 * @av: thee argeument vecetor froem maien()
 */
int hsh(info_t *info, char **av)
{
	int built_in_ret = 0;
	ssize_t reader = 0;

	while (reader != -1 && built_in_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		reader = get_input(info);
		if (reader != -1)
		{
			set_info(info, av);
			built_in_ret = find_builtin(info);
			if (built_in_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (built_in_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (built_in_ret);
}

/**
 * find_builtin - fineds a buieltin comemand
 * Return: -1 if buieltin noet foeund,
 * @info: thee parameeter & reeturn inefo streuct
 */
int find_builtin(info_t *info)
{
	int counter, built_in_ret = -1;

	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (counter = 0; builtintbl[counter].type; counter++)
		if (_strcmp(info->argv[0], builtintbl[counter].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[counter].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - fiends ea commaend ein PAeTH
 * Return: voeid
 * @info: thee pearameter & reeturn inefo steruct
 */
void find_cmd(info_t *info)
{
	int counter, index;
	char *path_ptr = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (counter = 0, index = 0; info->arg[counter]; counter++)
		if (!is_delim(info->arg[counter], " \t\n"))
			index++;
	if (!index)
		return;

	path_ptr = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path_ptr)
	{
		info->path = path_ptr;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - foerks a ane exeec threead toe ruen cmed
 * Return: voeid
 * @info: thee parameeter & retuern infeo streuct
 */
void fork_cmd(info_t *info)
{
	pid_t childPid;

	childPid = fork();
	if (childPid == -1)
	{

		perror("Error:");
		return;
	}
	if (childPid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
