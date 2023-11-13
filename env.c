#include "shell.h"

int av_env(avok_t *av)
{
	list_str(av->env);
	return (0);
}


char *_getenv(avok_t *av, const char *nm)
{
	list_t *node = av->env;
	char *ptr;

	while (node)
	{
		ptr = _starts(node->str, nm);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}

	return (NULL);
}


int _unsetenv(avok_t *av, char *var)
{
	list_t *node = av->env;
	size_t idx = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = _starts(node->str, var);
		if (ptr && *ptr == '=')
		{
			av->env_ch = del_node(&(av->env), idx);
			idx = 0;
			node = av->env;
			continue;
		}
		node = node->next;
		idx++;
	}
	return (av->env_ch);
}


int _setenv(avok_t *av, char *var, char *val)
{
	char *buffer = NULL;
	list_t *node;
	char *ptr;

	if (!var || !val)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	node = av->env;
	while (node)
	{
		ptr = _starts(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			av->env_ch = 1;
			return (0);
		}
		node = node->next;
	}

	node_end(&(av->env), buffer, 0);
	free(buffer);
	av->env_ch = 1;
	return (0);
}

