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
    return(SUCCESS);
}
char    *add_north(int fd)
{
    char    *line;

    while ()
}
char    *add_south(int fd)
{

}
char    *add_west(int fd)
{

}
char    *add_eart(int fd)
{

}
int     parce_direction(int fd, t_map **map)
{
    if (!((*map)->north = add_north(fd)))
        return (FAILURE);
    if (!((*map)->south = add_south(fd)))
        return (FAILURE);
    if (!((*map)->west = add_west(fd)))
            return (FAILURE);
    if (!((*map)->east = add_east(fd)))
            return (FAILURE);
    return (SUCCESS);
}