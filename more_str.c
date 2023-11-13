#include "shell.h"

char **strtow(char *str, char *dec)
{
	int i, j, k, m;
	int nwds = 0;
	char **src;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dec)
		dec = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!_isdelim(str[i], dec) && (_isdelim(str[i + 1], dec) || !str[i + 1]))
			nwds++;

	if (nwds == 0)
		return (NULL);
	src = malloc((1 + nwds) * sizeof(char *));
	if (!src)
		return (NULL);
	for (i = 0, j = 0; j < nwds; j++)
	{
		while (_isdelim(str[i], dec))
			i++;
		k = 0;
		while (!_isdelim(str[i + k], dec) && str[i + k])
			k++;
		src[j] = malloc((k + 1) * sizeof(char));
		if (!src[j])
		{
			for (k = 0; k < j; k++)
				free(src[k]);
			free(src);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			src[j][m] = str[i++];
		src[j][m] = 0;
	}
	src[j] = NULL;
	return (src);
}


char **_strtow(char *str, char d)
{
	int i, j, k, m;
	int nwds = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			nwds++;
	if (nwds == 0)
		return (NULL);
	s = malloc((1 + nwds) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nwds; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}


char *_strncat(char *dest, char *src, int n)
{
	int idx, j;
	char *str = dest;

	idx = 0;
	j = 0;
	while (dest[idx] != '\0')
		idx++;
	while (src[j] != '\0' && j < n)
	{
		dest[idx] = src[j];
		idx++;
		j++;
	}
	if (j < n)
		dest[idx] = '\0';
	return (str);
}


char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}


char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

