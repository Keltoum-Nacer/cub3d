#include "../include_file/cub3d.h"

void init_flag(t_bres_flag *s, t_point p0, t_point p1)
{
    s->dx = abs(p1.x_ind - p0.x_ind);
    s->dy = abs(p1.y_ind - p0.y_ind);
    if (p0.x_ind < p1.x_ind)
        s->sx = 1;
    else
        s->sx = -1;
    if (p0.y_ind < p1.y_ind)
        s->sy = 1;
    else
        s->sy = -1;
    s->err = s->dx - s->dy;
}

void bresenham(t_point p0, t_point p1, t_data *data)
{
    t_bres_flag s;
    int e2;

    init_flag(&s, p0, p1);
    while (1)
    {
        if (data->map.map[p0.y_ind / 30][p0.x_ind / 30] == '1')
            break;
        my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, 0X00FF00);
        if (p0.x_ind == p1.x_ind && p0.y_ind == p1.y_ind)
            break;
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx;
        }
        else if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy;
        }
    }
}