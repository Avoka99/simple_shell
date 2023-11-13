#include "shell.h"

int av_setenv(avok_t *av)
{
	if (av->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(av, av->argv[1], av->argv[2]))
		return (0);
	return (1);
}


int av_unsetenv(avok_t *av)
{
	int idx;

	if (av->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (idx = 1; idx <= av->argc; idx++)
		_unsetenv(av, av->argv[idx]);

	return (0);
}


int env_list(avok_t *av)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		node_end(&node, environ[i], 0);
	av->env = node;

	return (0);
}


char **user_env(avok_t *av)
{
	if (!av->environ || av->env_ch)
	{
		av->environ = list_to_str(av->env);
		av->env_ch = 0;
	}

	return (av->environ);
}

