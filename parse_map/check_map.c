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
            && (*map)->map[i][j] != 'W' && (*map)->map[i][j] != 'D')
                return(ft_put_str("Invalid mapp character!\n", NULL), FAILURE);
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
        if ((i > 0 && i < (*map)->height - 1) &&
            ((*map)->map[i][j] != '1' || (*map)->map[i][ft_strlen((*map)->map[i]) - 1] != '1'))
            {
                printf("====> %s\n", (*map)->map[i]);
            return (ft_put_str("Invalid mappp!\n", NULL), FAILURE);
            } 
        while ((*map)->map[i][j])
        {
            if ((i == 0 || i == (*map)->height - 1) && 
                ((*map)->map[i][j] != '1' && !ft_whitespace((*map)->map[i][j])))
                return (ft_put_str("Invalid mapi!\n", NULL), FAILURE);
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
        while((*map)->map[i][j])// ila kant lmap makatslalish bnewline kaytsegfaulta i don't know why
        {
            while((*map)->map[i][j] && (*map)->map[i][j] != ' ' )
                j++;
            if (j && (*map)->map[i][j - 1] != '1')
                return (ft_put_str("Invalid mapa!\n", NULL), FAILURE);
            while((*map)->map[i][j] && (*map)->map[i][j] == ' ')
            {
                if((*map)->map[i - 1][j] != '1' || (*map)->map[i + 1][j] != '1')
                    return (ft_put_str("Invalid maapaa!\n", NULL), FAILURE);
                j++;
            }
            if (j < len && ((*map)->map[i][j] != '1'))
                return (ft_put_str("Invalid mapaa!\n", NULL), FAILURE);
            if((*map)->map[i][j])
                j++;
        }
        i++;
    }
    return(SUCCESS);
}

int check_doors(t_map **map)
{
    int i;
    int j;

    i = 0;
    while((*map)->map[i])
    {
        j = 0;
        while((*map)->map[i][j])
        {
            if ((*map)->map[i][j] == 'D' && ((*map)->map[i][j - 1] != '1' || (*map)->map[i][j + 1] != '1'))
                return(ft_put_str("the doors should be surrounded by walls!", NULL), FAILURE);
            j++;
        }
        i++;
    }
    return(SUCCESS);
}
int height_map(int fdd)
{
    char    *line;
    int     count;

    count = 0;
    while((line = get_next_line(fdd)))
    {
        count++;
        free(line);
    }
    close(fdd);
    return(count);
}

int    read_map(int fd, int fdd, t_map **map)
{
    char    *line;
    int     i;

    i = 0;
    (*map)->height = height_map(fdd);
    printf("the height of map is %d\n", (*map)->height);
    while((line = get_next_line(fd)))
    {
        if (ft_strcmp(line, "\n"))
        {
            (*map)->map[i] = ft_strtrim(line, " \n\t\v\f\r");
            printf("---->%s\n", (*map)->map[i]);
            i++;
        }
        else if(i > 0 && i < (*map)->height)
        {
            free(line);
            return (ft_put_str("Invalid mapii!\n", NULL), FAILURE);
        }
        free(line);
    }
    (*map)->map[i] = NULL;
    (*map)->height = i;
    return(SUCCESS);
}    

int parse_map(int fd, int fdd, t_map **map)
{
    if(!read_map(fd, fdd, map))
        return(FAILURE);
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
    if(!check_doors(map))
        return(FAILURE);
    return(SUCCESS);
}