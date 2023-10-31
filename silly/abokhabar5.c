#include "myshell.h"

void _custom_print_error(char *custom_str) {
    int custom_i = 0;

    if (!custom_str) {
        return;
    }
    while (custom_str[custom_i] != '\0') {
        _custom_put_error_char(custom_str[custom_i]);
        custom_i++;
    }
}

int _custom_put_error_char(char custom_c) {
    static int custom_i;
    static char custom_buf[CUSTOM_WRITE_BUF_SIZE];

    if (custom_c == CUSTOM_BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUF_SIZE) {
        write(2, custom_buf, custom_i);
        custom_i = 0;
    }
    if (custom_c != CUSTOM_BUF_FLUSH) {
        custom_buf[custom_i++] = custom_c;
    }
    return 1;
}

int _custom_put_char_fd(char custom_c, int custom_fd) {
    static int custom_i;
    static char custom_buf[CUSTOM_WRITE_BUF_SIZE];

    if (custom_c == CUSTOM_BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUF_SIZE) {
        write(custom_fd, custom_buf, custom_i);
        custom_i = 0;
    }
    if (custom_c != CUSTOM_BUF_FLUSH) {
        custom_buf[custom_i++] = custom_c;
    }
    return 1;
}

int _custom_puts_fd(char *custom_str, int custom_fd) {
    int custom_i = 0;

    if (!custom_str) {
        return 0;
    }
    while (*custom_str) {
        custom_i += _custom_put_char_fd(*custom_str++, custom_fd);
    }
    return custom_i;
}
