#include "myshell.h"

int _my_custom_env(custom_info_t *custom_info) {
    custom_print_list_str(custom_info->custom_env);
    return 0;
}

char *custom_get_custom_env(custom_info_t *custom_info, const char *custom_name) {
    custom_list_t *custom_node = custom_info->custom_env;
    char *custom_p;

    while (custom_node) {
        custom_p = custom_starts_with(custom_node->str, custom_name);
        if (custom_p && *custom_p) {
            return custom_p;
        }
        custom_node = custom_node->next;
    }
    return NULL;
}

int _my_custom_setenv(custom_info_t *custom_info) {
    if (custom_info->custom_argc != 3) {
        custom_err_puts("Incorrect number of arguments\n");
        return 1;
    }
    if (_custom_set_custom_env(custom_info, custom_info->custom_argv[1], custom_info->custom_argv[2])) {
        return 0;
    }
    return 1;
}

int _my_custom_unsetenv(custom_info_t *custom_info) {
    int custom_i;

    if (custom_info->custom_argc == 1) {
        custom_err_puts("Too few arguments.\n");
        return 1;
    }

    for (custom_i = 1; custom_info->custom_argc; custom_i++) {
        custom_unset_custom_env(custom_info, custom_info->custom_argv[custom_i]);
    }

    return 0;
}

int custom_populate_custom_env_list(custom_info_t *custom_info) {
    custom_list_t *custom_node = NULL;
    size_t custom_i;

    for (custom_i = 0; custom_environ[custom_i]; custom_i++) {
        custom_add_node_end(&custom_node, custom_environ[custom_i], 0);
    }
    custom_info->custom_env = custom_node;
    return 0;
}
