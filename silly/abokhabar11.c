#include "myshell.h"

void _custom_clear_custom_info(info_t *custom_info) {
    custom_info->custom_arg = NULL;
    custom_info->custom_argv = NULL;
    custom_info->custom_path = NULL;
    custom_info->custom_argc = 0;
}

void _custom_set_custom_info(info_t *custom_info, char **custom_av) {
    int custom_i = 0;

    custom_info->custom_fname = custom_av[0];
    if (custom_info->custom_arg) {
        custom_info->custom_argv = _custom_strtow(custom_info->custom_arg, " \t");
        if (!custom_info->custom_argv) {
            custom_info->custom_argv = _custom_malloc(sizeof(char *) * 2);
            if (custom_info->custom_argv) {
                custom_info->custom_argv[0] = _custom_strdup(custom_info->custom_arg);
                custom_info->custom_argv[1] = NULL;
            }
        }
        for (custom_i = 0; custom_info->custom_argv && custom_info->custom_argv[custom_i]; custom_i++)
            ;
        custom_info->custom_argc = custom_i;

        _custom_replace_custom_alias(custom_info);
        _custom_replace_custom_vars(custom_info);
    }
}

void _custom_free_custom_info(info_t *custom_info, int all) {
    _custom_ffree(custom_info->custom_argv);
    custom_info->custom_argv = NULL;
    custom_info->custom_path = NULL;
    if (all) {
        if (!custom_info->custom_cmd_buf) {
            _custom_free(custom_info->custom_arg);
        }
        if (custom_info->custom_env) {
            _custom_free_list(&(custom_info->custom_env));
        }
        if (custom_info->custom_history) {
            _custom_free_list(&(custom_info->custom_history));
        }
        if (custom_info->custom_alias) {
            _custom_free_list(&(custom_info->custom_alias));
        }
        _custom_ffree(custom_info->custom_environ);
        custom_info->custom_environ = NULL;
        _custom_bfree((void **)custom_info->custom_cmd_buf);
        if (custom_info->custom_readfd > 2) {
            close(custom_info->custom_readfd);
        }
        _custom_putchar(CUSTOM_BUF_FLUSH);
    }
}
