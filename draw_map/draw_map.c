#include "../include_file/cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= WIN_HEIGHT || y < 0 || y >= WIN_WIDTH)
        return;
    offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
    *((unsigned int *)(data->image_addr + offset)) = color;
}

void draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < 30)
    {
        hor = 0;
        while (hor < 30)
        {
            my_mlx_pixel_put(mlx, 30 * i + hor, 30 * j + ver, color);
            hor++;
        }
        ver++;
    }
}
void draw_player(int x, int y, int color, t_mlx *mlx)
{
            my_mlx_pixel_put(mlx, x  , y , color);
}
void draw_raycasting(t_data *data)
{
    t_point x;

    x.x_ind = data->map.p.p_x;
    x.y_ind = data->map.p.p_y;

    double fov = 30 * PI / 180.0;
    int num_rays = WIN_WIDTH / 2;
    double angle_step = fov / num_rays;

    double current_angle = data->map.p.angle * PI / 180.0;
    double a =0;
    while (a < 30 * PI / 180)   
    {
        if(current_angle == 2 * PI)
            current_angle = 0;
        bresenham(x, current_angle, data);
        current_angle += angle_step;
         a = a + angle_step;
    }
    // a = 30;
    current_angle = data->map.p.angle * PI / 180.0;
    while(a >= 0)
        {
        if(current_angle == 0)
            current_angle = 2 * PI;
        current_angle -= angle_step;
        bresenham(x,current_angle, data);
        a -= angle_step;
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
