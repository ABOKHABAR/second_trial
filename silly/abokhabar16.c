#include "shell.h"

int fnx1(void **p)
{
    if (p && *p)
    {
        free(*p);
        *p = NULL;
        return 1;
    }
    return 0;
}
