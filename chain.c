#include "shell.h"

int rep_str(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


int rep_vars(avok_t *av)
{
	int idx = 0;
	list_t *node;

	for (idx = 0; av->argv[idx]; idx++)
	{
		if (av->argv[idx][0] != '$' || !av->argv[idx][1])
			continue;

		if (!_strcmp(av->argv[idx], "$?"))
		{
			rep_str(&(av->argv[idx]),
					_strdup(con_num(av->status, 10, 0)));
			continue;
		}

		if (!_strcmp(av->argv[idx], "$$"))
		{
			rep_str(&(av->argv[idx]),
					_strdup(con_num(getpid(), 10, 0)));
			continue;
		}

		node = node_begins(av->env, &av->argv[idx][1], '=');
		if (node)
		{
			rep_str(&(av->argv[idx]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}

		rep_str(&av->argv[idx], _strdup(""));

	}

	return (0);
}


void check_chain(avok_t *av, char *buffer, size_t *p, size_t i, size_t size)
{
	size_t idx = *p;

	if (av->cmmd == CMD_AND)
	{
		if (av->status)
		{
			buffer[i] = 0;
			idx = size;
		}
	}

	if (av->cmmd == CMD_OR)
	{
		if (!av->status)
		{
			buffer[i] = 0;
			idx = size;
		}
	}

	*p = idx;
}


int chain_com(avok_t *av, char *buffer, size_t *size)
{
	size_t idx = *size;

	if (buffer[idx] == '|' && buffer[idx + 1] == '|')
	{
		buffer[idx] = 0;
		idx++;
		av->cmmd = CMD_OR;
	}

	else if (buffer[idx] == '&' && buffer[idx + 1] == '&')
	{
		buffer[idx] = 0;
		idx++;
		av->cmmd = CMD_AND;
	}

	else if (buffer[idx] == ';') /* found end of this command */
	{
		buffer[idx] = 0; /* replace semicolon with null */
		av->cmmd = CMD_CHAIN;
	}

	else
		return (0);
	*size = idx;
	return (1);
}


int print_dec(int input, int fd)
{
	int count = 0;
	int (*__putchar)(char) = _putchar;
	int idx;
	unsigned int ac, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		ac = -input;
		__putchar('-');
		count++;
	}
	else
		ac = input;
	current = ac;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (ac / idx)
		{
			__putchar('0' + current / idx);
			count++;
		}
		current %= idx;
	}

	__putchar('0' + current);
	count++;
	return (count);
}

