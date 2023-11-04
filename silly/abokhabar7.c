#include "myshell.h"

char *_custom_copy_str(char *custom_dest, char *custom_src, int custom_n) {
    int custom_i, custom_j;
    char *custom_s = custom_dest;

    custom_i = 0;
    while (custom_src[custom_i] != '\0' && custom_i < custom_n - 1) {
        custom_dest[custom_i] = custom_src[custom_i];
        custom_i++;
    }

    if (custom_i < custom_n) {
        custom_j = custom_i;
        while (custom_j < custom_n) {
            custom_dest[custom_j] = '\0';
            custom_j++;
        }
    }
    return custom_s;
}

char *_custom_concatenate_str(char *custom_dest, char *custom_src, int custom_n) {
    int custom_i, custom_j;
    char *custom_s = custom_dest;

    custom_i = 0;
    custom_j = 0;
    while (custom_dest[custom_i] != '\0') {
        custom_i++;
    }

    while (custom_src[custom_j] != '\0' && custom_j < custom_n) {
        custom_dest[custom_i] = custom_src[custom_j];
        custom_i++;
        custom_j++;
    }

    if (custom_j < custom_n) {
        custom_dest[custom_i] = '\0';
    }
    return custom_s;
}

char *_custom_find_char(char *custom_str, char custom_c) {
    do {
        if (*custom_str == custom_c) {
            return custom_str;
        }
    } while (*custom_str++ != '\0');
    return NULL;
}
