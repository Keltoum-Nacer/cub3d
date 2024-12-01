#include "../include_file/cub3d.h"

int file_cub(int fd, char *name)
{
    int flag = 0;
    if (fd < 0)
    {
        write(2, name, ft_strlen(name) -1);
        write(2, " No such file\n", 14);
        return (FAILURE);
    }
    if (name[ft_strlen(name) -1] != 'b' || name[ft_strlen(name) - 2] != 'u' || name[ft_strlen(name) -3] != 'c' || name[ft_strlen(name) -4] != '.')
                    flag++;
    if (!ft_strcmp(name, ".cub") || flag)
    {
        write(2, name, ft_strlen(name) -1);
        write(2, "Not a .cub file\n", 16);
        return (FAILURE);
    }
    return (SUCCESS);
}
