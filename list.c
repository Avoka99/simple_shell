#include "shell.h"

size_t list_str(const list_t *head)
{
	size_t idx = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		idx++;
	}

	return (idx);
}


size_t list_len(const list_t *head)
{
	size_t idx = 0;

	while (head)
	{
		head = head->next;
		idx++;
	}

	return (idx);
}


size_t print_list(const list_t *head)
{
	size_t idx = 0;

	while (head)
	{
		_puts(con_num(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		idx++;
	}

	return (idx);
}


char **list_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head);
	size_t j;
	char **strs;
	char *chars;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		chars = malloc(_strlen(node->str) + 1);
		if (!chars)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		chars = _strcpy(chars, node->str);
		strs[i] = chars;
	}

	strs[i] = NULL;
	return (strs);
}


int hist_list(avok_t *av, char *buffer, int linec)
{
	list_t *node = NULL;

	if (av->hist)
		node = av->hist;
	node_end(&node, buffer, linec);

	if (!av->hist)
		av->hist = node;

	return (0);
}

