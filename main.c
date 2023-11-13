#include "shell.h"

int main(int num, char **ac)
{
	avok_t av[] = { AVOK_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (num == 2)
	{
		fd = open(ac[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ac[0]);
				_eputs(": 0: Can't open ");
				_eputs(ac[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		av->rdfd = fd;
	}

	env_list(av);
	rd_hist(av);
	exec_main(av, ac);
	return (EXIT_SUCCESS);
}

