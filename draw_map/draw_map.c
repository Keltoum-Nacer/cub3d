#include "../include_file/cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
    *((unsigned int *)(data->image_addr + offset)) = color;
}

void draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < WALL_DIM)
    {
        hor = 0;
        while (hor < WALL_DIM)
        {
            my_mlx_pixel_put(mlx, WALL_DIM* i + hor, WALL_DIM * j + ver, color);
            hor++;
        }
        ver++;
    }
}

double  degree_to_rad(float fov)
{
    double rad;

    rad = fov * PI / 180.0;
    return(rad); 
}

void draw_player(int x, int y, int color, t_mlx *mlx)
{
    my_mlx_pixel_put(mlx, x, y, color);
}
void draw_raycasting(t_data *data)
{
    double fov;
    t_point x;
    fov = degree_to_rad(30);
    double angle_step = fov / NUM_RAYS;
    double alpha = 0;
    double current_angle = degree_to_rad(data->map.p.angle);
    x.x_ind = data->map.p.p_x;
    x.y_ind = data->map.p.p_y;

    while (alpha <= fov)
    {
        if (current_angle == 2 * PI)
            current_angle = 0;
        bresenham(x, current_angle, data);
        current_angle += angle_step;
        alpha += angle_step;
    }
    alpha = fov;
    current_angle = degree_to_rad(data->map.p.angle);
    while (alpha >= 0)
    {
        if (current_angle == 0)
            current_angle = 2 * PI;
        bresenham(x, current_angle, data);
        current_angle -= angle_step;
        alpha -= angle_step;
    }
}

void    calculate_distance(t_point p0, t_point p1, t_data *data)
{
    data->map.p.ray_dist = sqrt(powf(p0.x_ind - p1.x_ind, 2.)  + powf(p0.y_ind - p1.y_ind, 2.));
}

void    draw_wall(t_data *data, t_point p0, double alpha)
{
    (void)alpha;
    double dis_to_proj;
    double  wall_height;
    double  precise_dist;

    dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(alpha - data->map.p.angle));
    precise_dist = data->map.p.ray_dist * cos(alpha - data->map.p.angle);
    wall_height = (dis_to_proj / precise_dist) * WALL_DIM;
    bresenham_wall(p0, wall_height, data);
}

void draw_map(t_data *data)
{
    int i = 0;
    int j = 0;
    while (i < data->map.height * 64)
    {
        j = 0;
        while (j < data->map.width * 64)
        {
            if (i < (data->map.height * 64) / 2)
                my_mlx_pixel_put(&data->mlx, j, i , 0xFEAFEC);
            else
                my_mlx_pixel_put(&data->mlx, j, i , data->map.F_color);
            j++;
        }
        i++;
    }
    draw_player(data->map.p.p_x, data->map.p.p_y, 0XFFFFFFFF, &data->mlx);
    draw_raycasting(data);
}
