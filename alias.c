#include "shell.h"

int av_alias(avok_t *av)
{
	list_t *node = NULL;
	int idx = 0;
	char *ptr = NULL;

	if (av->argc == 1)
	{
		node = av->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (idx = 1; av->argv[idx]; idx++)
	{
		ptr = _strchr(av->argv[idx], '=');
		if (ptr)
			set_alias(av, av->argv[idx]);
		else
			print_alias(node_begins(av->alias, av->argv[idx], '='));
	}

	return (0);
}


int set_alias(avok_t *av, char *str)
{
	char *ptr;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(av, str));

	unset_alias(av, str);
	return (node_end(&(av->alias), str, 0) == NULL);
}


int unset_alias(avok_t *av, char *str)
{
	int result;
	char *ptr;
	char c;

	ptr = _strchr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	result = del_node(&(av->alias),
		node_index(av->alias, node_begins(av->alias, str, -1)));
	*ptr = c;
	return (result);
}


int print_alias(list_t *node)
{
	char *ac = NULL;
	char *ptr = NULL;

	if (node)
	{
		ptr = _strchr(node->str, '=');
		for (ac = node->str; ac <= ptr; ac++)
		_putchar(*ac);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}


int rep_alias(avok_t *av)
{
	list_t *node;
	int idx;
	char *ptr;

	for (idx = 0; idx < 10; idx++)
	{
		node = node_begins(av->alias, av->argv[0], '=');
		if (!node)
			return (0);
		free(av->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		av->argv[0] = ptr;
	}

	return (1);
}

