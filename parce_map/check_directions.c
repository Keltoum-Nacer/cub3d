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
char *extract_directory_path(int fd, int flag)
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
        return (free(d), free(line), NULL);
    return (free(line), d);
}

int parce_direction(int fd, t_map **map)
{
    char    *line;
    if (!((*map)->north = extract_directory_path(fd, 0)))
        return (FAILURE);
    if (!((*map)->south = extract_directory_path(fd, 1)))
        return (FAILURE);
    if (!((*map)->west = extract_directory_path(fd, 2)))
        return (FAILURE);
    if (!((*map)->east = extract_directory_path(fd, 3)))
        return (FAILURE);
    line = ft_getline(fd);
    if (line[0] != '\n')
    {
        write(2, DUP, 12);
        free(line);
        return (FAILURE);
    }
    return (free(line), SUCCESS);
}