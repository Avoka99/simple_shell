#include "shell.h"

char *_path(avok_t *av, char *str, char *cmd)
{
	int pos = 0;
	int idx = 0;
	char *path;

	if (!str)
		return (NULL);
	if ((_strlen(cmd) > 2) && _starts(cmd, "./"))
	{
		if (exec(av, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!str[idx] || str[idx] == ':')
		{
			path = dup_chars(str, pos, idx);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (exec(av, path))
				return (path);
			if (!str[idx])
				break;
			pos = idx;
		}

		idx++;
	}

	return (NULL);
}


char *dup_chars(char *str, int start, int stop)
{
	int idx = 0;
	static char buffer[1024];
	int k = 0;

	for (k = 0, idx = start; idx < stop; idx++)
		if (str[idx] != ':')
			buffer[k++] = str[idx];
	buffer[k] = 0;
	return (buffer);
}


ssize_t rd_buffer(avok_t *av, char *buffer, size_t *size)
{
	ssize_t result = 0;

	if (*size)
		return (0);

	result = read(av->rdfd, buffer, READ_BUF_SIZE);
	if (result >= 0)
		*size = result;

	return (result);
}


ssize_t enter_buffer(avok_t *av, char **buffer, size_t *size)
{
	ssize_t result = 0;
	size_t len = 0;

	if (!*size) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sig);
#if USE_GETLINE
		result = getline(buffer, &len, stdin);
#else
		result = _getline(av, buffer, &len);
#endif
		if (result > 0)
		{
			if ((*buffer)[result - 1] == '\n')
			{
				(*buffer)[result - 1] = '\0'; /* remove trailing newline */
				result--;
			}

			av->lc_flag = 1;
			rm_cmm(*buffer);
			hist_list(av, *buffer, av->histc++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*size = result;
				av->cmd = buffer;
			}
		}
	}

	return (result);
}


int _inter(avok_t *av)
{
	return (isatty(STDIN_FILENO) && av->rdfd <= 2);
}

