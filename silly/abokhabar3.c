#include "myshell.h"

int _my_custom_history(custom_info_t *custom_info) {
    custom_print_list(custom_info->history);
    return 0;
}

int custom_unset_custom_alias(custom_info_t *custom_info, char *custom_str) {
    char *custom_p, custom_c;
    int custom_ret;

    custom_p = _custom_strchr(custom_str, '=');
    if (!custom_p) {
        return 1;
    }
    custom_c = *custom_p;
    *custom_p = 0;
    custom_ret = custom_delete_node_at_index(&(custom_info->custom_alias),
        custom_get_node_index(custom_info->custom_alias, custom_node_starts_with(custom_info->custom_alias, custom_str, -1)));
    *custom_p = custom_c;
    return custom_ret;
}

int custom_set_custom_alias(custom_info_t *custom_info, char *custom_str) {
    char *custom_p;

    custom_p = _custom_strchr(custom_str, '=');
    if (!custom_p) {
        return 1;
    }
    if (!*++custom_p) {
        return custom_unset_custom_alias(custom_info, custom_str);
    }
    custom_unset_custom_alias(custom_info, custom_str);
    return (custom_add_node_end(&(custom_info->custom_alias), custom_str, 0) == NULL);
}

int custom_print_custom_alias(custom_list_t *custom_node) {
    char *custom_p = NULL, *custom_a = NULL;

    if (custom_node) {
        custom_p = _custom_strchr(custom_node->str, '=');
        for (custom_a = custom_node->str; custom_a <= custom_p; custom_putchar(*custom_a);
        custom_putchar('\'');
        custom_puts(custom_p + 1);
        custom_puts("'\n");
        return 0;
    }
    return 1;
}

int _my_custom_alias(custom_info_t *custom_info) {
    int custom_i = 0;
    char *custom_p = NULL;
    custom_list_t *custom_node = NULL;

    if (custom_info->custom_argc == 1) {
        custom_node = custom_info->custom_alias;
        while (custom_node) {
            custom_print_custom_alias(custom_node);
            custom_node = custom_node->next;
        }
        return 0;
    }
    for (custom_i = 1; custom_info->custom_argv[custom_i]; custom_i++) {
        custom_p = _custom_strchr(custom_info->custom_argv[custom_i], '=');
        if (custom_p) {
            custom_set_custom_alias(custom_info, custom_info->custom_argv[custom_i]);
        } else {
            custom_print_custom_alias(custom_node_starts_with(custom_info->custom_alias, custom_info->custom_argv[custom_i], '='));
        }
    }
    return 0;
}
