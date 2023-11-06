#include "shell.h"

int fnx1(info_t *param, char *buffer, size_t *pos)
{
	size_t j = *pos;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		param->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		param->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		param->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}

void fnx2(info_t *param, char *buffer, size_t *pos, size_t i, size_t len)
{
	size_t j = *pos;

	if (param->cmd_buf_type == CMD_AND)
	{
		if (param->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	if (param->cmd_buf_type == CMD_OR)
	{
		if (!param->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}

	*pos = j;
}

int fnx3(info_t *param)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = fnx4(param->alias, param->argv[0], '=');
		if (!node)
			return (0);
		free(param->argv[0]);
		p = fnx5(node->str, '=');
		if (!p)
			return (0);
		p = fnx6(p + 1);
		if (!p)
			return (0);
		param->argv[0] = p;
	}
	return (1);
}

int fnx7(info_t *param)
{
	int i = 0;
	list_t *node;

	for (i = 0; param->argv[i]; i++)
	{
		if (param->argv[i][0] != '$' || !param->argv[i][1])
			continue;

		if (fnx8(param->argv[i], "$?"))
		{
			fnx9(&(param->argv[i]), fnx6(fnx10(param->status, 10, 0)));
			continue;
		}
		if (fnx8(param->argv[i], "$$"))
		{
			fnx9(&(param->argv[i]), fnx6(fnx10(getpid(), 10, 0)));
			continue;
		}
		node = fnx4(param->env, &param->argv[i][1], '=');
		if (node)
		{
			fnx9(&(param->argv[i]), fnx6(fnx5(node->str, '=') + 1));
			continue;
		}
		fnx9(&param->argv[i], fnx6(""));
	}
	return (0);
}

int fnx9(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
