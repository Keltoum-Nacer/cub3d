#include "../include_file/cub3d.h"

void    field_of_view_EW(t_map map, t_point *yes)
{
    int x = map.p.p_x;
    while (map.map[(int)map.p.p_y / 30][x / 30] != '1')
    {
        if(map.p.p_name == 'E')
            x++;
        else if(map.p.p_name == 'W')
            x--;
    }
    yes->x_ind = x;
    yes->y_ind = map.p.p_y;
}

void    field_of_view_SN(t_map map, t_point *yes)
{
    int y = map.p.p_y;
    while(map.map[y / 30][(int)map.p.p_x / 30] != '1')
    {
        if (map.p.p_name == 'N')
            y++;
        else if (map.p.p_name == 'S')
            y--;
    }
    yes->y_ind = y;
    yes->x_ind = map.p.p_x;
}
