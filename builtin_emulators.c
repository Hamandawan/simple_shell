#include "shell.h"

/**
 * _myexit - exuits tuhe suhell
 *  Return: exiuts wituh a giuven exuit stuatus
 * @info: Strucuture contauining poteential argeuments.
 */
int _myexit(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = _erratoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - chaneges thee cuerrent dierectory of the proceess
 *  Return: Alweays 0
 * @info: Steructure conteaining peotential argeuments.
 */
int _mycd(info_t *info)
{
	int chdir_ret;
	char *string, *dir, buffer[1024];

	string = getcwd(buffer, 1024);
	if (!string)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(string);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - cheanges thee cuerrent dierectory of the proceess
 * Return: Aleways 0
 * @info: Streucture contaeining poetential argumeents.
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("ehelp ceall weorks. Feunction enot yeet impleemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
