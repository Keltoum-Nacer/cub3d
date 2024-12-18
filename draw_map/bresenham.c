#include "../include_file/cub3d.h"


void init_flag(t_bres_flag *s, t_point p0, t_point p1)
{
    s->dx = abs((int)p1.x_ind - (int)p0.x_ind);
    s->dy = abs((int)p1.y_ind - (int)p0.y_ind);
    if (p0.x_ind < p1.x_ind)
        s->sx = 1;
    else if (p0.x_ind > p1.x_ind)
        s->sx = -1;
    if (p0.y_ind < p1.y_ind)
        s->sy = 1;
    else if (p0.y_ind > p1.y_ind)
        s->sy = -1;
    s->err = s->dx - s->dy;
}
void bresenham_wall(t_point p0, double wall_height, t_data *data)
{
    t_bres_flag s;
    t_point p1;
    p1.x_ind = p0.x_ind;
    p1.y_ind = wall_height;
    init_flag(&s, p0, p1);
    while (1)
    {
        if ((int)p0.y_ind == (int)p1.y_ind)
            break;
        my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, 0xFFFFFF);
        p0.y_ind += s.sy;
    }
}

void bresenham(t_point p0, double alpha, t_data *data)
{
    t_bres_flag s;
    int e2;
    t_point p1;
    t_point player;

    player.x_ind = data->map.p.p_x;
    player.y_ind = data->map.p.p_y;
    p1.x_ind = p0.x_ind + 20000 * cos(alpha);
    p1.y_ind = 20000 * sin(alpha) + p0.y_ind;
    init_flag(&s, p0, p1);
    while (1)
    {
        if (data->map.map[(int)p0.y_ind / 64][(int)p0.x_ind / 64] == '1')
        {
            data->map.p.dist = calculate_distance(p0, player);
            draw_wall(p0, data, alpha);
            break;
        }
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx;
        }
        if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy;
        }
    }
}