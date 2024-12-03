#include "../include_file/cub3d.h"

int valid_character(t_map **map)
{
    int i;
    int j;
    int count;

    i = 0;
    count = 0;
    while((*map)->map[i])
    {
        j = 0;
        while((*map)->map[i][j])
        {
            if((*map)->map[i][j] != ' '&& (*map)->map[i][j] != '0' && (*map)->map[i][j] != '1' 
            && (*map)->map[i][j] != 'N' && (*map)->map[i][j] != 'S' && (*map)->map[i][j] != 'E' 
            && (*map)->map[i][j] != 'W' && (*map)->map[i][j] != '\n')
                return(ft_put_str("Invalid map!\n", NULL), FAILURE);
            if ((*map)->map[i][j] == 'N' || (*map)->map[i][j] == 'S' || (*map)->map[i][j] == 'E' || (*map)->map[i][j] == 'W')
                count++;
            j++;
        }
        i++;
    }
    if (count != 1)
        return(ft_put_str("Invalid map, it should contain one player!\n", NULL), FAILURE);
    return(SUCCESS);
}

int surrounded_by_1(t_map **map)
{
    int i;
    int j;

    i = 0;
    while ((*map)->map[i])
    {
        j = 0;
        while ((*map)->map[i][j] == ' ')
            j++;
        if ((i > 0 && i < (*map)->height - 1) &&
            ((*map)->map[i][j] != '1' || (*map)->map[i][ft_strlen((*map)->map[i]) - 2] != '1')) 
            return (ft_put_str("Invalid mappp!\n", NULL), FAILURE);
        while ((*map)->map[i][j])
        {
            while ((*map)->map[i][j] == ' ')
                j++;
            if ((i == 0 || i == (*map)->height - 1) && 
                ((*map)->map[i][j] != '1' && (*map)->map[i][j] != '\n'))
                return (ft_put_str("Invalid map!\n", NULL), FAILURE);
            j++;
        }
        i++;
    }
    return (SUCCESS);
}

int closed_by_1(t_map **map)
{
    int i;
    int j;
    int len;

    i = 0;
    while((*map)->map[i])
    {
        j = 0;
        len = ft_strlen((*map)->map[i]);
        while((*map)->map[i][j])
        {
            while(j < len && (*map)->map[i][j] != ' ' && (*map)->map[i][j] != '\n')
                j++;
            if (j && (*map)->map[i][j - 1] != '1') 
                return (ft_put_str("Invalid mapa!\n", NULL), FAILURE);
            while(j < len && (*map)->map[i][j] == ' ')
                j++;
            if (j < len && ((*map)->map[i][j] != '1' && (*map)->map[i][j] != '\n'))
                return (ft_put_str("Invalid mapaa!\n", NULL), FAILURE);
            j++;
        }
        i++;
    }
    return(SUCCESS);
}

void    read_map(int fd, t_map **map)
{
    char    *line;
    int     i;

    i = 0;
    while((line = get_next_line(fd)))
    {
        if (strcmp(line, "\n"))
        {
            (*map)->map[i] = ft_strdup(line);
            printf("---->%s\n", (*map)->map[i]);
            i++;
        }
        free(line);
    }
    (*map)->map[i] = NULL;
    (*map)->height = i;
}    

int parse_map(int fd, t_map **map)
{
    read_map(fd, map);
    if(!(*map)->map[0])
        return (ft_put_str("Empty map!\n", NULL), FAILURE);
    if ((*map)->height <= 2)
        return (ft_put_str("Map too small!\n", NULL), FAILURE);
    if(!valid_character(map))
        return(FAILURE);
    if(!surrounded_by_1(map))
        return(FAILURE);
    if(!closed_by_1(map))
        return(FAILURE);
    return(SUCCESS);
}