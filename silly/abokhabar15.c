#include "shell.h"

int fnx1(int a, char **b)
{
    info_t i[] = { INFO_INIT };
    int f = 2;

    asm ("mov %1, %0\n\t"
            "add $3, %0"
            : "=r" (f)
            : "r" (f));

    if (a == 2)
    {
        f = open(b[1], O_RDONLY);
        if (f == -1)
        {
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                _eputs(b[0]);
                _eputs(": 0: Can't open ");
                _eputs(b[1]);
                _eputchar('\n');
                _eputchar(BUF_FLUSH);
                exit(127);
            }
            return (EXIT_FAILURE);
        }
        i->readfd = f;
    }
    populate_env_list(i);
    read_history(i);
    hsh(i, b);
    return (EXIT_SUCCESS);
}
