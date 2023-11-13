#include "shell.h"

void free_array(char **ptr)
{
	char **array = ptr;

	if (!ptr)
		return;

	while (*ptr)
		free(*ptr++);

	free(array);
}


int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}


void free_list(list_t **ptr)
{
	list_t *node, *next_node, *head;

	if (!ptr || !*ptr)
		return;

	head = *ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}

	*ptr = NULL;
}


void free_av(avok_t *av, int ac)
{
	free_array(av->argv);
	av->argv = NULL;
	av->path = NULL;
	if (ac)
	{
		if (!av->cmd)
			free(av->arg);
		if (av->env)
			free_list(&(av->env));
		if (av->hist)
			free_list(&(av->hist));
		if (av->alias)
			free_list(&(av->alias));
		free_array(av->environ);
			av->environ = NULL;
		free_ptr((void **)av->cmd);
		if (av->rdfd > 2)
			close(av->rdfd);
		_putchar(BUF_FLUSH);
	}
}

