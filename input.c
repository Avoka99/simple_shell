#include "shell.h"

ssize_t user_input(avok_t *av)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t result = 0;
	char **buffer_ptr = &(av->arg);
	char *ptr;

	_putchar(BUF_FLUSH);
	result = enter_buffer(av, &buffer, &len);
	if (result == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		ptr = buffer + i; /* get pointer for return */
		check_chain(av, buffer, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (chain_com(av, buffer, &j))
				break;
			j++;
		}
		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			av->cmmd = CMD_NORM;
		}
		*buffer_ptr = ptr; /* pass back pointer to current command position */
		return (_strlen(ptr)); /* return length of current command */
	}
	*buffer_ptr = buffer; /* else not a chain, pass back buffer from _getline() */
	return (result); /* return length of buffer from _getline() */
}


int _getline(avok_t *av, char **ptr, size_t *size)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t result = 0;
	ssize_t s = 0;
	char *p = NULL;
	char *new_p = NULL;
	char *c;

	p = *ptr;
	if (p && size)
		s = *size;
	if (i == len)
		i = len = 0;
	result = rd_buffer(av, buffer, &len);
	if (result == -1 || (result == 0 && len == 0))
		return (-1);
	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (size)
		*size = s;
	*ptr = p;
	return (s);
}


char *_starts(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);

	return ((char *)haystack);
}


char *con_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}


void rm_cmm(char *buffer)
{
	int idx;

	for (idx = 0; buffer[idx] != '\0'; idx++)
		if (buffer[idx] == '#' && (!idx || buffer[idx - 1] == ' '))
		{
			buffer[idx] = '\0';
			break;
		}
}

