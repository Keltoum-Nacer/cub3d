#include "../include_files/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    mlx_do_sync(data->mlx.mlx);
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}

void validate_move(t_data *data, double new_x, double new_y, int flag_x, int flag_y)
{

    if (data->map.map[(int)((new_y ) / WALL_DIM)][(int)((new_x ) / WALL_DIM)] != '1')
    {
        data->map.p.p_x = new_x - flag_x;
        data->map.p.p_y = new_y - flag_y;
    }
}

int handle_key(int keycode, t_data *data)
{
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    double angle = data->map.p.angle;
    if (keycode == KEY_W)
    {
        double new_x = (data->map.p.p_x + SPEED * cos(angle)) + CO * cos(angle);
        double new_y = (data->map.p.p_y + SPEED * sin(angle)) + CO *sin(angle);
        validate_move(data, new_x, new_y, CO * cos(angle), CO * sin(angle));
    }

    if (keycode == KEY_S)
    {
        double new_x = (data->map.p.p_x - SPEED * cos(angle)) - CO * cos(angle);
        double new_y = (data->map.p.p_y - SPEED * sin(angle)) - CO *sin(angle);
        validate_move(data, new_x, new_y, -CO * cos(angle), -CO * sin(angle));
    }
    if (keycode == KEY_A)
    {
        double new_x = data->map.p.p_x - SPEED * cos(angle + PI / 2) - CO * cos(angle + PI/2);
        double new_y = data->map.p.p_y - SPEED * sin(angle + PI / 2)  - CO *sin(angle + PI/ 2);
        validate_move(data, new_x, new_y,  -CO * cos(angle+ PI/2), -CO * sin(angle+PI/2));
    }
    if (keycode == KEY_D)
    {
        double new_x = data->map.p.p_x + SPEED * cos(angle + PI / 2) + CO *cos(angle + PI/ 2);
        double new_y = data->map.p.p_y + SPEED * sin(angle + PI / 2) + CO *sin(angle + PI/ 2);
        validate_move(data, new_x, new_y,CO * cos(angle+ PI/2), CO * sin(angle+PI/2));
    }
    if (keycode == KEY_LEFT)
    {
        data->map.p.angle += 0.10;
        if (data->map.p.angle > 2 * PI)
            data->map.p.angle -= 2 * PI;
    }
    if (keycode == KEY_RIGHT)
    {
        data->map.p.angle -= 0.10;
        if (data->map.p.angle < 0)
            data->map.p.angle += 2 * PI;
    }
    return (move_player(data), 1);
}
