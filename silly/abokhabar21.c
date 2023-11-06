#include "shell.h"

char *fnx1(char *dst, char *src)
{
	int i = 0;

	if (dst == src || src == 0)
		return (dst);

	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char *fnx2(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		len++;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (len++; len--;)
		ret[len] = *--str;

	return (ret);
}

void fnx3(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		fnx4(str[i]);
		i++;
	}
}

int fnx4(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
