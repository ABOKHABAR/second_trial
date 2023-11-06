#include "shell.h"

int fnx1(info_t *info, char *p)
{
    struct stat s;

    (void)info;
    if (!p || stat(p, &s))
        return 0;

    if (s.st_mode & S_IFREG)
    {
        return 1;
    }
    return 0;
}

char *fnx2(char *ps, int st, int sp)
{
    static char b[1024];
    int i = 0, k = 0;

    for (k = 0, i = st; i < sp; i++)
        if (ps[i] != ':')
            b[k++] = ps[i];
    b[k] = 0;
    return b;
}

char *fnx3(info_t *info, char *ps, char *c)
{
    int i = 0, cp = 0;
    char *p;

    if (!ps)
        return NULL;
    if ((_strlen(c) > 2) && starts_with(c, "./"))
    {
        if (fnx1(info, c))
            return c;
    }
    while (1)
    {
        if (!ps[i] || ps[i] == ':')
        {
            p = fnx2(ps, cp, i);
            if (!*p)
                _strcat(p, c);
            else
            {
                _strcat(p, "/");
                _strcat(p, c);
            }
            if (fnx1(info, p))
                return p;
            if (!ps[i])
                break;
            cp = i;
        }
        i++;
    }
    return NULL;
}
