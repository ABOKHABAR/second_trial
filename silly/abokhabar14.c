#include "shell.h"

size_t fnx1(const list_t *lst)
{
    size_t x = 0;

    while (lst)
    {
        lst = lst->next;
        x++;
    }
    return x;
}

char **fnx2(list_t *hd)
{
    list_t *n = hd;
    size_t x = fnx1(hd), y;
    char **s;
    char *t;

    if (!hd || !x)
        return NULL;
    s = malloc(sizeof(char *) * (x + 1));
    if (!s)
        return NULL;
    for (x = 0; n; n = n->next, x++)
    {
        t = malloc(_strlen(n->str) + 1);
        if (!t)
        {
            for (y = 0; y < x; y++)
                free(s[y]);
            free(s);
            return NULL;
        }

        t = _strcpy(t, n->str);
        s[x] = t;
    }
    s[x] = NULL;
    return s;
}

size_t fnx3(const list_t *lst)
{
    size_t x = 0;

    while (lst)
    {
        _puts(convert_number(lst->num, 10, 0));
        _putchar(':');
        _putchar(' ');
        _puts(lst->str ? lst->str : "(nil)");
        _puts("\n");
        lst = lst->next;
        x++;
    }
    return x;
}

list_t *fnx4(list_t *n, char *p, char c)
{
    char *s = NULL;

    while (n)
    {
        s = starts_with(n->str, p);
        if (s && ((c == -1) || (*s == c)))
            return n;
        n = n->next;
    }
    return NULL;
}

ssize_t fnx5(list_t *hd, list_t *n)
{
    size_t x = 0;

    while (hd)
    {
        if (hd == n)
            return x;
        hd = hd->next;
        x++;
    }
    return -1;
}
