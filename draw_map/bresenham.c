#include "../include_file/cub3d.h"

// void init_flag(t_bres_flag *s, t_player p, t_point p1)
// {
//     s->dx = abs(p1.x_ind - p.p_x);
//     s->dy = abs(p1.y_ind - p.p_y);
//     if (p.p_x < p1.x_ind)
//         s->sx = 1;
//     else if (p.p_x > p1.x_ind)
//         s->sx = -1;
//     if (p.p_y < p1.y_ind)
//         s->sy = 1;
//     else if (p.p_y > p1.y_ind)
//         s->sy = -1;
//     s->err = s->dx - s->dy;
// }

// void bresenham(double alpha, t_data *data)
// {
//     t_bres_flag s;
//     int e2;
//     t_point p1;

//     p1.x_ind = data->map.p.p_x + data->map.p.p_x * cos(alpha);
//     p1.y_ind = data->map.p.p_y * sin(alpha) + data->map.p.p_y;
//     init_flag(&s, data->map.p, p1); 
//     while (1)
//     {
//         if (data->map.map[(int )data->map.p.p_y / 30][(int) data->map.p.p_x / 30] == '1')
//             break;
//         my_mlx_pixel_put(&data->mlx, data->map.p.p_x, data->map.p.p_y, 0x00FF00);
//         e2 = s.err*2;
//         if (e2 > -s.dy)
//         {
//             s.err -= s.dy;
//             data->map.p.p_x += s.sx;
//         }
//         if (e2 < s.dx)
//         {
//            s.err += s.dx;
//             data->map.p.p_y += s.sy;
//         }
//     }
// }

void init_flag(t_bres_flag *s, t_point p0, t_point p1)
{
    s->dx = abs(p1.x_ind - p0.x_ind);
    s->dy = abs(p1.y_ind - p0.y_ind);
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

void bresenham(t_point p0, double alpha, t_data *data)
{
    t_bres_flag s;
    int e2;
    t_point p1;

    p1.x_ind = p0.x_ind + p0.x_ind* cos(alpha);
    p1.y_ind = p0.x_ind * sin(alpha) + p0.y_ind;
    init_flag(&s, p0, p1); 
    while (1)
    {
        if (data->map.map[p0.y_ind / 64][p0.x_ind / 64] == '1')
            break;
        my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, 0x00FF00);
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