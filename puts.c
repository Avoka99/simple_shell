#include "shell.h"

int _putchar(char c)
{
	static int idx;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(1, buffer, idx);
		idx = 0;
	}
	if (c != BUF_FLUSH)
		buffer[idx++] = c;
	return (1);
}


void _puts(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		_putchar(str[idx]);
		idx++;
	}
}


void _eputs(char *str)
{
	int idx = 0;

	if (!str)
		return;
	while (str[idx] != '\0')
	{
		_eputchar(str[idx]);
		idx++;
	}
}


int _putfd(char c, int fd)
{
	static int idx;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, idx);
		idx = 0;
	}
	if (c != BUF_FLUSH)
		buffer[idx++] = c;
	return (1);
}


int _eputchar(char c)
{
	static int idx;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || idx >= WRITE_BUF_SIZE)
	{
		write(2, buffer, idx);
		idx = 0;
	}
	if (c != BUF_FLUSH)
		buffer[idx++] = c;
	return (1);
}

