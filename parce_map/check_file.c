#include "../include_file/cub3d.h"

int file_cub(int fd, char *name)
{
    int flag = 0;
    if (fd < 0)
    {
        write(2, name, ft_strlen(name) - 1);
        write(2, " No such file\n", 14);
        return (FAILURE);
    }
    if (name[ft_strlen(name) - 1] != 'b' || name[ft_strlen(name) - 2] != 'u' || name[ft_strlen(name) - 3] != 'c' || name[ft_strlen(name) - 4] != '.')
        flag++;
    if (!ft_strcmp(name, ".cub") || flag)
    {
        write(2, name, ft_strlen(name) - 1);
        write(2, NOT_CUB, 17);
        return (FAILURE);
    }
    return (SUCCESS);
}

int file_xpm(char *name)
{
    int fd;

    name[ft_strlen(name) - 1] = '\0';
    if (!ft_strcmp(name, ".cub"))
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