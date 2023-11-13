#include "shell.h"

void clear_av(avok_t *av)
{
	av->arg = NULL;
	av->argv = NULL;
	av->path = NULL;
	av->argc = 0;
}


void set_av(avok_t *av, char **ac)
{
	int idx = 0;

	av->fname = ac[0];
	if (av->arg)
	{
		av->argv = strtow(av->arg, " \t");
		if (!av->argv)
		{
			av->argv = malloc(sizeof(char *) * 2);
			if (av->argv)
			{
				av->argv[0] = _strdup(av->arg);
				av->argv[1] = NULL;
			}
		}
		for (idx = 0; av->argv && av->argv[idx]; idx++)
			;
		av->argc = idx;
		rep_alias(av);
		rep_vars(av);
	}
}

