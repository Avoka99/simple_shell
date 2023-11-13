#include "shell.h"

int av_hist(avok_t *av)
{
	print_list(av->hist);
	return (0);
}


int wrt_hist(avok_t *av)
{
	ssize_t fd;
	char *fname = user_histf(av);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = av->hist; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}


char *user_histf(avok_t *av)
{
	char *buffer;
	char *dir;

	dir = _getenv(av, "HOME=");
	if (!dir)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, dir);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);

	return (buffer);
}


int rd_hist(avok_t *av)
{
	int i, last = 0, linec = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL;
	char *fname = user_histf(av);

	if (!fname)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			hist_list(av, buffer + last, linec++);
			last = i + 1;
		}
	if (last != i)
		hist_list(av, buffer + last, linec++);
	free(buffer);
	av->histc = linec;
	while (av->histc-- >= HIST_MAX)
		del_node(&(av->hist), 0);
	rnum_hist(av);
	return (av->histc);
}


int rnum_hist(avok_t *av)
{
	list_t *node = av->hist;
	int idx = 0;

	while (node)
	{
		node->num = idx++;
		node = node->next;
	}
	return (av->histc = idx);
}

