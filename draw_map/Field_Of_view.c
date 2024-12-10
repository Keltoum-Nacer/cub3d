#include "../include_file/cub3d.h"
void    field_of_view(t_map map, t_point *yes)
{
    int x = map.p.p_x;
    while (map.map[(int)map.p.p_y / 30][x / 30] != '1')
        x++;
    yes->x_ind = x;
    yes->y_ind = map.p.p_y;
}
