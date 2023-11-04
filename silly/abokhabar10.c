#include "myshell.h"

char **_custom_get_custom_environment(info_t *custom_info) {
    if (!custom_info->custom_environment || custom_info->custom_environment_changed) {
        custom_info->custom_environment = _custom_list_to_custom_strings(custom_info->custom_env);
        custom_info->custom_environment_changed = 0;
    }
    return custom_info->custom_environment;
}

int _custom_unset_custom_environment(info_t *custom_info, char *custom_var) {
    list_t *custom_node = custom_info->custom_env;
    size_t custom_i = 0;
    char *custom_p;

    if (!custom_node || !custom_var) {
        return 0;
    }

    while (custom_node) {
        custom_p = _custom_starts_with(custom_node->custom_str, custom_var);
        if (custom_p && *custom_p == '=') {
            custom_info->custom_environment_changed = _custom_delete_node_at_index(&(custom_info->custom_env), custom_i);
            custom_i = 0;
            custom_node = custom_info->custom_env;
            continue;
        }
        custom_node = custom_node->next;
        custom_i++;
    }
    return custom_info->custom_environment_changed;
}

int _custom_set_custom_environment(info_t *custom_info, char *custom_var, char *custom_value) {
    char *custom_buf = NULL;
    list_t *custom_node;
    char *custom_p;

    if (!custom_var || !custom_value) {
        return 0;
    }

    custom_buf = _custom_malloc(_custom_string_length(custom_var) + _custom_string_length(custom_value) + 2);
    if (!custom_buf) {
        return 1;
    }
    _custom_string_copy(custom_buf, custom_var);
    _custom_string_concatenate(custom_buf, "=");
    _custom_string_concatenate(custom_buf, custom_value);
    custom_node = custom_info->custom_env;
    while (custom_node) {
        custom_p = _custom_starts_with(custom_node->custom_str, custom_var);
        if (custom_p && *custom_p == '=') {
            _custom_free(custom_node->custom_str);
            custom_node->custom_str = custom_buf;
            custom_info->custom_environment_changed = 1;
            return 0;
        }
        custom_node = custom_node->next;
    }
    _custom_add_node_end(&(custom_info->custom_env), custom_buf, 0);
    _custom_free(custom_buf);
    custom_info->custom_environment_changed = 1;
    return 0;
}
