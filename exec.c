#include "shell.h"

int exec(avok_t *av, char *path)
{
	struct stat st;

	(void)av;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}

	return (0);
}


void find_exec(avok_t *av)
{
	char *path = NULL;
	int idx;
	int j;

	av->path = av->argv[0];
	if (av->lc_flag == 1)
	{
		av->l_c++;
		av->lc_flag = 0;
	}
	for (idx = 0, j = 0; av->arg[idx]; idx++)
		if (!_isdelim(av->arg[idx], " \t\n"))
			j++;
	if (!j)
		return;

	path = _path(av, _getenv(av, "PATH="), av->argv[0]);
	if (path)
	{
		av->path = path;
		exec_com(av);
	}
	else
	{
		if ((_inter(av) || _getenv(av, "PATH=")
					|| av->argv[0][0] == '/') && exec(av, av->argv[0]))
			exec_com(av);
		else if (*(av->arg) != '\n')
		{
			av->status = 127;
			print_error(av, "not found\n");
		}
	}
}


void exec_com(avok_t *av)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(av->path, av->argv, user_env(av)) == -1)
		{
			free_av(av, 1);

			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(av->status));
		if (WIFEXITED(av->status))
		{
			av->status = WEXITSTATUS(av->status);
			if (av->status == 126)
				print_error(av, "Permission denied\n");
		}
	}
}


int exec_main(avok_t *av, char **ac)
{
	ssize_t rd = 0;
	int j = 0;

	while (rd != -1 && j != -2)
	{
		clear_av(av);
		if (_inter(av))
			_puts("Avok_shell$ ");
		_eputchar(BUF_FLUSH);
		rd = user_input(av);
		if (rd != -1)
		{
			set_av(av, ac);
			j = av_builtin(av);
			if (j == -1)
				find_exec(av);
		}
		else if (_inter(av))
			_putchar('\n');
		free_av(av, 0);
	}
	wrt_hist(av);
	free_av(av, 1);
	if (!_inter(av) && av->status)
		exit(av->status);
	if (j == -2)
	{
		if (av->err_no == -1)
			exit(av->status);
		exit(av->err_no);
	}
	return (j);
}

