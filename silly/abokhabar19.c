#include "shell.h"

int fnx1(info_t *i, char **av)
{
	ssize_t r = 0;
	int br = 0;

	while (r != -1 && br != -2)
	{
		clear_info(i);
		if (interactive(i))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(i);
		if (r != -1)
		{
			set_info(i, av);
			br = find_builtin(i);
			if (br == -1)
				find_command(i);
		}
		else if (interactive(i))
			_putchar('\n');
		free_info(i, 0);
	}
	write_history(i);
	free_info(i, 1);
	if (!interactive(i) && i->status)
		exit(i->status);
	if (br == -2)
	{
		if (i->err_num == -1)
			exit(i->status);
		exit(i->err_num);
	}
	return br;
}

int fnx2(info_t *i)
{
	int j, br = -1;
	builtin_table tbl[] = {
		{"exit", fnx3},
		{"env", fnx4},
		{"help", fnx5},
		{"history", fnx6},
		{"setenv", fnx7},
		{"unsetenv", fnx8},
		{"cd", fnx9},
		{"alias", fnx10},
		{NULL, NULL}
	};

	for (j = 0; tbl[j].type; j++)
		if (_strcmp(i->argv[0], tbl[j].type) == 0)
		{
			i->line_count++;
			br = tbl[j].func(i);
			break;
	}
	return br;
}

void fnx3(info_t *i)
{
	char *p = NULL;
	int j, k;

	i->path = i->argv[0];
	if (i->linecount_flag == 1)
	{
		i->line_count++;
		i->linecount_flag = 0;
	}
	for (j = 0, k = 0; i->arg[j]; j++)
		if (!is_delim(i->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	p = find_path(i, _getenv(i, "PATH="), i->argv[0]);
	if (p)
	{
		i->path = p;
		fork_command(i);
	}
	else
	{
		if ((interactive(i) || _getenv(i, "PATH=")
					|| i->argv[0][0] == '/') && is_cmd(i, i->argv[0]))
			fork_command(i);
		else if (*(i->arg) != '\n')
		{
			i->status = 127;
			print_error(i, "not found\n");
		}
	}
}

void fnx4(info_t *i)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(i->path, i->argv, get_environ(i)) == -1)
		{
			free_info(i, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(i->status));
		if (WIFEXITED(i->status))
		{
			i->status = WEXITSTATUS(i->status);
			if (i->status == 126)
				print_error(i, "Permission denied\n");
		}
	}
}
