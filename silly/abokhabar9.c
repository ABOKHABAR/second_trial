#include "myshell.h"

ssize_t _custom_input_buffer(info_t *custom_info, char **custom_buf, size_t *custom_len) {
    ssize_t custom_r = 0;
    size_t custom_len_p = 0;

    if (!*custom_len) {
        free(*custom_buf);
        *custom_buf = NULL;
        signal(SIGINT, _custom_sigint_handler);
#if USE_CUSTOM_GETLINE
        custom_r = _custom_getline(custom_buf, &custom_len_p, stdin);
#else
        custom_r = _custom_get_line(custom_info, custom_buf, &custom_len_p);
#endif
        if (custom_r > 0) {
            if ((*custom_buf)[custom_r - 1] == '\n') {
                (*custom_buf)[custom_r - 1] = '\0';
                custom_r--;
            }
            custom_info->linecount_flag = 1;
            _custom_remove_comments(*custom_buf);
            _custom_build_history_list(custom_info, *custom_buf, custom_info->histcount++);
            custom_len = custom_r;
            custom_info->cmd_buf = custom_buf;
        }
    }
    return custom_r;
}

ssize_t _custom_get_input(info_t *custom_info) {
    static char *custom_buf;
    static size_t custom_i, custom_j, custom_len;
    ssize_t custom_r = 0;
    char **custom_buf_p = &(custom_info->arg), *custom_p;

    _custom_put_char(BUF_FLUSH);
    custom_r = _custom_input_buffer(custom_info, &custom_buf, &custom_len);
    if (custom_r == -1) {
        return -1;
    }
    if (custom_len) {
        custom_j = custom_i;
        custom_p = custom_buf + custom_i;

        _custom_check_chain(custom_info, custom_buf, &custom_j, custom_i, custom_len);
        while (custom_j < custom_len) {
            if (_custom_is_chain(custom_info, custom_buf, &custom_j)) {
                break;
            }
            custom_j++;
        }
        custom_i = custom_j + 1;
        if (custom_i >= custom_len) {
            custom_i = custom_len = 0;
            custom_info->cmd_buf_type = CMD_NORM;
        }
        *custom_buf_p = custom_p;
        return _custom_string_length(custom_p);
    }
    *custom_buf_p = custom_buf;
    return custom_r;
}

ssize_t _custom_read_buffer(info_t *custom_info, char *custom_buf, size_t *custom_i) {
    ssize_t custom_r = 0;
    if (*custom_i) {
        return 0;
    }
    custom_r = read(custom_info->readfd, custom_buf, READ_CUSTOM_BUF_SIZE);
    if (custom_r >= 0) {
        *custom_i = custom_r;
    }
    return custom_r;
}

int _custom_get_line(info_t *custom_info, char **custom_ptr, size_t *custom_length) {
    static char custom_buf[READ_CUSTOM_BUF_SIZE];
    static size_t custom_i, custom_len;
    size_t custom_k;
    ssize_t custom_r = 0, custom_s = 0;
    char *custom_p = NULL, *custom_new_p = NULL, *custom_c;
    custom_p = *custom_ptr;

    if (custom_p && custom_length) {
        custom_s = *custom_length;
    }
    if (custom_i == custom_len) {
        custom_i = custom_len = 0;
    }
    custom_r = _custom_read_buffer(custom_info, custom_buf, &custom_len);
    if (custom_r == -1 || (custom_r == 0 && custom_len == 0)) {
        return -1;
    }
    custom_c = _custom_find_char(custom_buf + custom_i, '\n');
    custom_k = custom_c ? 1 + (unsigned int)(custom_c - custom_buf) : custom_len;
    custom_new_p = _custom_realloc(custom_p, custom_s, custom_s ? custom_s + custom_k : custom_k + 1);
    if (!custom_new_p) {
        return custom_p ? free(custom_p), -1 : -1;
    }
    if (custom_s) {
        _custom_concatenate_string(custom_new_p, custom_buf + custom_i, custom_k - custom_i);
    } else {
        _custom_copy_string(custom_new_p, custom_buf + custom_i, custom_k - custom_i + 1);
    }
    custom_s += custom_k - custom_i;
    custom_i = custom_k;
    custom_p = custom_new_p;
    if (custom_length) {
        *custom_length = custom_s;
    }
    *custom_ptr = custom_p;
    return custom_s;
}

void _custom_sigint_handler(__attribute__((unused))int custom_sig_num) {
    _custom_puts("\n");
    _custom_puts("$ ");
    _custom_put_char(BUF_FLUSH);
}
