#include "../include_file/cub3d.h"

int validate_position(char *line, int flag)
{
    if (!flag && (line[0] != 'N' || line[1] != 'O'))
        return (FAILURE);
    if (flag == 1 && (line[0] != 'S' || line[1] != 'O'))
        return (FAILURE);
    if (flag == 2 && (line[0] != 'W' || line[1] != 'E'))
        return (FAILURE);
    if (flag == 3 && (line[0] != 'E' || line[1] != 'A'))
        return (FAILURE);
    return (SUCCESS);
}
char *add_dir(int fd, int flag)
{
    char *line;
    char *d;

    line = ft_getline(fd);
    while (line[0] == '\n')
    {
        free(line);
        line = ft_getline(fd);
    }
    if (!validate_position(line, flag))
        return (ft_put_str(INV_TEX, NULL), free(line), NULL);
    d = ft_strdup(ft_strchr(line, 't'));
    if (!file_xpm(d))
        return (free(d), FAILURE);
    return (d);
}

int parce_direction(int fd, t_map **map)
{
    char    *line;
    if (!((*map)->north = add_dir(fd, 0)))
        return (FAILURE);
    if (!((*map)->south = add_dir(fd, 1)))
        return (FAILURE);
    if (!((*map)->west = add_dir(fd, 2)))
        return (FAILURE);
    if (!((*map)->east = add_dir(fd, 3)))
        return (FAILURE);
    if (line[0] != '\n')
        return (FAILURE);
    return (SUCCESS);
}