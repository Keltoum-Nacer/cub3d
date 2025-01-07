#include "../include_files/cub3d_bonus.h"

int extract_and_validate_int(char *line, int *pos)
{
    int i;
    int ret;
    char *nmbr;

    i = 0;
    while (ft_whitespace(line[0]))
        line++;
    while (ft_isdigit(line[i]))
        i++;
    *pos = *pos + i;
    nmbr = ft_substr(line, 0, i);
    if (!nmbr[0])
        return(ft_put_str(INV_RGB, NULL), -1);
    ret = ft_atoi(nmbr);
    if (ret >= 0 && ret <= 255)
    {
        if (line[0] == ',')
            (*pos)++;
        return (free(nmbr), ret);
    }
    if (line[0] == ',')
        (*pos)++;
    return (-1);
}

long long transform_sequence(char *line)
{
    int c_red;
    int c_green;
    int c_blue;
    int pos;

    line++;
    pos = 0;
    while (ft_whitespace(line[0]))
        line++;
    if ((c_red = extract_and_validate_int(line, &pos)) == -1)
        return (-1);
    while (ft_whitespace(line[0]))
        line++;
    line++;
    if ((c_green = extract_and_validate_int(line + pos, &pos)) == -1)
        return (-1);
    while (ft_whitespace(line[0]))
        line++;
    line++;
    if ((c_blue = extract_and_validate_int(line + pos, &pos)) == -1)
        return (-1);
    return ((c_red << 16) | (c_green << 8) | c_blue);
}

int extract_color_value(int fd, int flag, t_map **map)
{
    char *line;
    int color;
    line = get_next_line(fd);
    while (line[0] == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    (*map)->height_text++;
    char *line_trim = ft_strtrim(line, " \n\r\f\v\t");
    if (!flag && line_trim[0] == 'F')
    {
        if ((color = transform_sequence(line_trim)) == -1)
            return (free(line_trim), free(line), -1);
        return (free(line_trim), free(line), color);
    }
    else if (flag && line_trim[0] == 'C')
    {
        if ((color = transform_sequence(line_trim)) == -1)
            return (free(line_trim), free(line), -1);
        return (free(line_trim), free(line), color);
    }
    ft_put_str(MIS_COL, NULL);
    return (-1);
}

int parse_color(int fd, t_map **map)
{
    if (((*map)->F_color = extract_color_value(fd, 0, map)) == -1)
        return (FAILURE);
    if (((*map)->C_color = extract_color_value(fd, 1, map)) == -1)
        return (FAILURE);
    return (SUCCESS);
}