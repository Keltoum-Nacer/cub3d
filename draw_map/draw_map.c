#include "../include_file/cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= WIN_WIDTH|| y < 0 || y >= WIN_HEIGHT)
        return;
    offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
    *((unsigned int *)(data->image_addr + offset)) = color;
}

void draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < 64)
    {
        hor = 0;
        while (hor < 64)
        {
            // printf("--->%d-->%d\n", 64* i + hor,64* j + ver);
            my_mlx_pixel_put(mlx, 64* i + hor, 64 * j + ver, color);
            hor++;
        }
        ver++;
    }
}
void draw_player(int x, int y, int color, t_mlx *mlx)
{
    my_mlx_pixel_put(mlx, x, y, color);
}
void draw_raycasting(t_data *data)
{
    double fov = 30 * PI / 180.0;
    int num_rays = 1920 / 2;
    t_point x;

    double angle_step = fov / num_rays;
    double alpha = 0;
    double current_angle = data->map.p.angle * PI / 180.0;
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
    current_angle = data->map.p.angle * PI / 180.0;
    while (alpha >= 0)
    {
        if (current_angle == 0)
            current_angle = 2 * PI;
        bresenham(x, current_angle, data);
        current_angle -= angle_step;
        alpha -= angle_step;
    }
}

void draw_map(t_data *data)
{
    int i = 0;
    int j = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == '1')
                draw_pixels(j, i, data->map.C_color, &data->mlx);
            else
                draw_pixels(j, i, data->map.F_color, &data->mlx);
            j++;
        }
        i++;
    }
    draw_player(data->map.p.p_x, data->map.p.p_y, 0XFFFFFFFF, &data->mlx);
    draw_raycasting(data);
}
