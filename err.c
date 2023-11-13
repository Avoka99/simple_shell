#include "shell.h"

int _putsfd(char *str, int fd)
{
	int idx = 0;

	if (!str)
		return (0);
	while (*str)
	{
		idx += _putfd(*str++, fd);
	}
	return (idx);
}


int err_atoi(char *str)
{
	int idx = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (idx = 0; str[idx] != '\0'; idx++)
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			result *= 10;
			result += (str[idx] - '0');
			if (result > INT_MAX)
				return (-1);
		}

		else
			return (-1);
	}

	return (result);
}


void print_error(avok_t *av, char *msg)
{
	_eputs(av->fname);
	_eputs(": ");
	print_dec(av->l_c, STDERR_FILENO);
	_eputs(": ");
	_eputs(av->argv[0]);
	_eputs(": ");
	_eputs(msg);
}


void handle_sig(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


int _atoi(char *str)
{
	int idx, output;
	int sign = 1;
	int flag = 0;
	unsigned int result = 0;

	for (idx = 0; str[idx] != '\0' && flag != 2; idx++)
	{
		if (str[idx] == '-')
			sign *= -1;
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[idx] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}

