#include "shell.h"

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *node;

	if (!head)
		return (NULL);
	node = malloc(sizeof(list_t));
	if (!node)
		return (NULL);
	_memset((void *)node, 0, sizeof(list_t));
	node->num = num;
	if (str)
	{
		node->str = _strdup(str);
		if (!node->str)
		{
			free(node);
			return (NULL);
		}
	}

	node->next = *head;
	*head = node;
	return (node);
}


list_t *node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


int del_node(list_t **head, unsigned int i)
{
	list_t *node, *old_node;
	unsigned int idx = 0;

	if (!head || !*head)
		return (0);

	if (!i)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (idx == i)
		{
			old_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}

		idx++;
		old_node = node;
		node = node->next;
	}

	return (0);
}


list_t *node_begins(list_t *head, char *p, char c)
{
	char *ptr = NULL;

	while (head)
	{
		ptr = _starts(head->str, p);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (head);
		head = head->next;
	}

	return (NULL);
}


ssize_t node_index(list_t *head, list_t *node)
{
	size_t idx = 0;

	while (head)
	{
		if (head == node)
			return (idx);
		head = head->next;
		idx++;
	}

	return (-1);
}

