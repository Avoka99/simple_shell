#include "shell.h"

int av_exit(avok_t *av)
{
	int exitcheck;

	if (av->argv[1]) /* If there is an exit arguement */
	{
		exitcheck = err_atoi(av->argv[1]);
		if (exitcheck == -1)
		{
			av->status = 2;
			print_error(av, "Illegal number: ");
			_eputs(av->argv[1]);
			_eputchar('\n');
			return (1);
		}

		av->err_no = err_atoi(av->argv[1]);
		return (-2);
	}

	av->err_no = -1;
	return (-2);
}


int av_help(avok_t *av)
{
	char **ar;

	ar = av->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*ar); /* temp att_unused workaround */
	return (0);
}


int av_builtin(avok_t *av)
{
	int idx;
	int j = -1;
	builtin_table bt[] = {
		{"exit", av_exit},
		{"env", av_env},
		{"help", av_help},
		{"history", av_hist},
		{"setenv", av_setenv},
		{"unsetenv", av_unsetenv},
		{"cd", av_cd},
		{"alias", av_alias},
		{NULL, NULL}
	};

	for (idx = 0; bt[idx].type; idx++)
		if (_strcmp(av->argv[0], bt[idx].type) == 0)
		{
			av->l_c++;
			j = bt[idx].func(av);
			break;
		}
	return (j);
}


int av_cd(avok_t *av)
{
	char *str, *dir;
	char buffer[1024];
	int j;

	str = getcwd(buffer, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!av->argv[1])
	{
		dir = _getenv(av, "HOME=");
		if (!dir)
			j = /* TODO: what should this be? */
				chdir((dir = _getenv(av, "PWD=")) ? dir : "/");
		else
			j = chdir(dir);
	}

	else if (_strcmp(av->argv[1], "-") == 0)
	{
		if (!_getenv(av, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(av, "OLDPWD=")), _putchar('\n');
		j = /* TODO: what should this be? */
			chdir((dir = _getenv(av, "OLDPWD=")) ? dir : "/");
	}
	else
		j = chdir(av->argv[1]);
	if (j == -1)
	{
		print_error(av, "can't cd to ");
		_eputs(av->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(av, "OLDPWD", _getenv(av, "PWD="));
		_setenv(av, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

