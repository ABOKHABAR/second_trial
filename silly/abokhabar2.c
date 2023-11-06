#include "myshell.h"

int _my_custom_exit(custom_info_t *custom_info)
{
	int exit_code_check;

	if (custom_info->args[1])
	{
		exit_code_check = _str_to_int(custom_info->args[1]);
		if (exit_code_check == -1)
		{
			custom_info->status = 2;
			custom_print_error(custom_info, "Illegal number: ");
			custom_err_puts(custom_info->args[1]);
			custom_err_putchar('\n');
			return (1);
		}
		custom_info->error_number = _str_to_int(custom_info->args[1]);
		return (-2);
	}
	custom_info->error_number = -1;
	return (-2);
}

int _my_custom_cd(custom_info_t *custom_info)
{
	char *source, *directory, buffer[1024];
	int chdir_result;

	source = _custom_getcwd(buffer, 1024);
	if (!source)
		custom_puts("TODO: >>getcwd failure emsg here<<\n"); }
	if (!custom_info->args[1])
{
		directory = _custom_getenv(custom_info, "HOME=");
		if (!directory)
			chdir_result = chdir(
					(directory = _custom_getenv(custom_info, "PWD="))
					? directory
					: "/"
);
	} else
{
			chdir_result = chdir(directory);
		}
	} else if (_custom_strcmp(custom_info->args[1], "-") == 0)
{
		if (!_custom_getenv(custom_info, "OLDPWD="))
		{
			custom_puts(source);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(_custom_getenv(custom_info, "OLDPWD="));
		custom_putchar('\n');
		chdir_result = chdir(
				(directory = _custom_getenv(custom_info, "OLDPWD="))
				? directory
				: "/"
);
	} else
{
		chdir_result = chdir(custom_info->args[1]);
	}
	if (chdir_result == -1)
{
		custom_print_error(custom_info, "can't cd to ");
		custom_err_puts(custom_info->args[1]);
		custom_err_putchar('\n');
	} else
{
		_custom_setenv(custom_info, "OLDPWD", _custom_getenv(custom_info, "PWD="));
		_custom_setenv(custom_info, "PWD", _custom_getcwd(buffer, 1024));
	}
	return (0);
}

int _my_custom_help(custom_info_t *custom_info)
{
	char **argument_array;

	argument_array = custom_info->args;
	custom_puts("help call works. Function not yet implemented \n");
	if (0)
	{
		custom_puts(*argument_array); /* temp att_unused workaround */
	}
	return (0);
}
