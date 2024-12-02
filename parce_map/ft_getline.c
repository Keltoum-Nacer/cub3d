#include "../include_file/cub3d.h"

char    *ft_getline(int fd)
{
    char    *buff;
    char    *tmp;
    char    *d;
    ssize_t size;

    buff = NULL;
    tmp = malloc(2);
    if (!tmp)
        return (NULL);
    while (1)
    {
        size = read(fd, tmp, 1);
        if (size < 0)
            return (NULL);
        tmp[1] = '\0';
        d = buff;
        buff = ft_strjoin(d, tmp);
        if (tmp[0] == '\n' || !tmp)
            return (free(tmp), free(d),buff);
        free(d);
    }
    return (NULL);
}