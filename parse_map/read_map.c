#include"../include_file/cub3d.h"

int height_map(int fdd)
{
    char    *line;
    int     count;

    count = 0;
    while((line = get_next_line(fdd)))
    {
        if(ft_strcmp(line, "\n"))
            count++;
        free(line);
    }
    close(fdd);
    return(count);
}


int check_player(t_map *map, char player, int i, int j)
{
    if(player == 'N' || player == 'S' || player == 'E' || player == 'W')
    {
        map->p.p_x = (float)j;
        map->p.p_y = (float)i;
        map->p.p_name = player;
        return (1);
    }
    return(0);
}

int valid_character(t_map *map)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while(map->map[i])
    {
        j = 0;
        while(map->map[i][j])
        {
            if(!ft_whitespace(map->map[i][j]) && map->map[i][j] != '0' && map->map[i][j] != '1' 
            && map->map[i][j] != 'N' && map->map[i][j] != 'S' && map->map[i][j] != 'E' 
            && map->map[i][j] != 'W' && map->map[i][j] != 'D')
                return(print_err(MAP), FAILURE);
            count += check_player(map, map->map[i][j], i, j);
            j++;
        }
        i++;
    }
    if (count != 1)
        return(print_err(PLAYER), FAILURE);
    return(SUCCESS);
}

int    read_map(int fd, int fdd, t_map *map)
{
    char    *line;
    int     i;

    i = 0;
    map->height = height_map(fdd);
    while((line = get_next_line(fd)))
    {
        while(line && !ft_strcmp(line, "\n") && i == 0)
        {
            free(line);
            line = get_next_line(fd);
        }
        if(line && ft_strcmp(line, "\n"))
        {
            map->map[i] = ft_strtrim(line, "\n");
            i++;
        }
        else if(line && i < map->height - map->height_text)
            return ( free(line),print_err(MAP), FAILURE);
        free(line);
    }
    map->map[i] = NULL;
    map->height = i;
    return(SUCCESS);
}
