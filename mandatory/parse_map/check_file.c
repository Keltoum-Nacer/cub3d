#include "../include_files/cub3d.h"

int file_cub(int fd, char *name)
{
    int flag = 0;
    if (fd < 0)
    {
        ft_put_str(ER_OPEN, name);
        return (FAILURE);
    }
    if (name[ft_strlen(name) - 1] != 'b' || name[ft_strlen(name) - 2] != 'u' || name[ft_strlen(name) - 3] != 'c' || name[ft_strlen(name) - 4] != '.')
        flag++;
    if (!ft_strcmp(name, ".cub") || flag)
    {
        ft_put_str(NOT_CUB, name);
        return (FAILURE);
    }
    return (SUCCESS);
}

int file_xpm(char *name)
{
    int fd;

    if (!ft_strcmp(name, ".xpm"))
    {
        ft_put_str(NOT_XPM, name);
        return (FAILURE);
    }
    if (name[ft_strlen(name) - 1] != 'm' || name[ft_strlen(name) - 2] != 'p' || name[ft_strlen(name) - 3] != 'x' || name[ft_strlen(name) - 4] != '.')
    {
        ft_put_str(NOT_XPM, name);
        return (FAILURE);
    }
    fd = open(name, O_RDONLY);
    if (fd < 0)
    {
        perror(name);
        return (FAILURE);
    }
    close(fd);
    return (SUCCESS);
}
