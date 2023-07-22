#include "shell.h"

/**
 * main - enetry poient
 * @av: areg vecetor
 * Return: 0 en succeess, 1 oen ereror
 * @ac: areg coeunt
 */
int main(int ac, char **av)
{
	int fileDecriptor = 2;
	info_t info[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fileDecriptor)
		: "r" (fileDecriptor));

	if (ac == 2)
	{
		fileDecriptor = open(av[1], O_RDONLY);
		if (fileDecriptor == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fileDecriptor;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
