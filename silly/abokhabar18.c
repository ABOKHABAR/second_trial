#include "shell.h"

char *fnx1(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return s;
}

void fnx2(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

void *fnx3(void *p, unsigned int old_size, unsigned int new_size)
{
	char *np;

	if (!p)
		return malloc(new_size);
	if (!new_size)
		return free(p), NULL;
	if (new_size == old_size)
		return p;

	np = malloc(new_size);
	if (!np)
		return NULL;

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		np[old_size] = ((char *)p)[old_size];
	free(p);
	return np;
}
