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
void bresenham_wall(t_point p0, int start, int end, t_data *data)
{
    int i = 0;
    while ( i < start)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, 0xFFFFFF);
        i++;
    }
    p0.y_ind = start;
    while (i < end)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, 0xFECBD8);
        i++;
    }
     while (i < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, 0xABCD286 );
        i++;
    }
}

void draw_wall(t_point p0, t_data *data, double alpha, int i)
{

    double dis_to_proj;
    double wall_height;
    double precise_dist;
    precise_dist = data->map.p.dist * cos(alpha - degree_to_rad(data->map.p.angle));

    dis_to_proj = (WIN_WIDTH/2) / tan(degree_to_rad(FOV / 2));

    wall_height = (dis_to_proj / precise_dist) * WALL_DIM;
    double ww= wall_height*10;
    if ((int)(ww) % 10 > 5)
        wall_height++;
     int start = (WIN_HEIGHT / 2) - (int)(wall_height / 2);
    int end = (WIN_HEIGHT / 2) + (int)(wall_height / 2);
    p0.x_ind = i;
    bresenham_wall(p0, start, end, data);
}

void bresenham(t_point p0, double alpha, t_data *data, int i)
{
    t_bres_flag s;
    int e2;
    t_point p1;
    t_point player;

    player.x_ind = data->map.p.p_x;
    player.y_ind = data->map.p.p_y;
    double max_ray_length = sqrt(pow(data->map.width * 64, 2) + pow(MAP_HEIGHT * 64, 2));
    p1.x_ind = p0.x_ind + max_ray_length * cos(alpha);
    p1.y_ind = max_ray_length * sin(alpha) + p0.y_ind;
    init_flag(&s, p0, p1);
    while (1)
    {
        if (data->map.map[(int)p0.y_ind / 64][(int)p0.x_ind / 64] == '1')
        {
            data->map.p.dist = calculate_distance(p0, player);
            draw_wall(p0,data,  alpha, i);
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
