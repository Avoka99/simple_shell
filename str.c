#include "shell.h"

int _strlen(char *str)
{
	int idx = 0;

	if (!str)
		return (0);

	while (*str++)
		idx++;
	return (idx);
}


int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


char *_strcat(char *dest, char *src)
{
	char *str = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (str);
}


char *_strcpy(char *dest, char *src)
{
	int idx = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[idx])
	{
		dest[idx] = src[idx];
		idx++;
	}
	dest[idx] = 0;
	return (dest);
}


char *_strdup(const char *str)
{
	int len = 0;
	char *chr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	chr = malloc(sizeof(char) * (len + 1));
	if (!chr)
		return (NULL);
	for (len++; len--;)
		chr[len] = *--str;
	return (chr);
}

