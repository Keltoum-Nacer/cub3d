#include "../include_files/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}

void validate_move(t_data *data, double new_x, double new_y, int flag_x, int flag_y)
{

    if (data->map.map[(int)((new_y) / WALL_DIM)][(int)((new_x) / WALL_DIM)] != '1')
    {
        data->map.p.p_x = new_x - flag_x;
        data->map.p.p_y = new_y - flag_y;
    }
}
void move_up_down(t_data *data, int keycode)
{
    if (keycode == KEY_W)
    {
        double new_x = (data->map.p.p_x + SPEED * cos(data->map.p.angle)) + CO * cos(data->map.p.angle);
        double new_y = (data->map.p.p_y + SPEED * sin(data->map.p.angle)) + CO * sin(data->map.p.angle);
        validate_move(data, new_x, new_y, CO * cos(data->map.p.angle), CO * sin(data->map.p.angle));
    }
    else
    {
        double new_x = (data->map.p.p_x - SPEED * cos(data->map.p.angle)) - CO * cos(data->map.p.angle);
        double new_y = (data->map.p.p_y - SPEED * sin(data->map.p.angle)) - CO * sin(data->map.p.angle);
        validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle), -CO * sin(data->map.p.angle));
    }
    move_player(data);
}

void move_left_right(t_data *data, int keycode)
{
    if (keycode == KEY_A)
    {
        double new_x = data->map.p.p_x - SPEED * cos(data->map.p.angle + PI / 2) - CO * cos(data->map.p.angle + PI / 2);
        double new_y = data->map.p.p_y - SPEED * sin(data->map.p.angle + PI / 2) - CO * sin(data->map.p.angle + PI / 2);
        validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle + PI / 2), -CO * sin(data->map.p.angle + PI / 2));
    }
    else
    {
        double new_x = data->map.p.p_x + SPEED * cos(data->map.p.angle + PI / 2) + CO * cos(data->map.p.angle + PI / 2);
        double new_y = data->map.p.p_y + SPEED * sin(data->map.p.angle + PI / 2) + CO * sin(data->map.p.angle + PI / 2);
        validate_move(data, new_x, new_y, CO * cos(data->map.p.angle + PI / 2), CO * sin(data->map.p.angle + PI / 2));
    }
    move_player(data);
}

void rot(t_data *data, int keycode)
{
    if (keycode == KEY_LEFT)
    {
        data->map.p.angle += 0.10;
        if (data->map.p.angle > 2 * PI)
            data->map.p.angle -= 2 * PI;
    }
    else
    {
        data->map.p.angle -= 0.10;
        if (data->map.p.angle < 0)
            data->map.p.angle += 2 * PI;
    }
    move_player(data);
}

int handle_key(int keycode, t_data *data)
{
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    if (keycode == KEY_W || keycode == KEY_S)
        move_up_down(data, keycode);
    if (keycode == KEY_A || keycode == KEY_D)
        move_left_right(data, keycode);
    if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
        rot(data, keycode);
    return (1);
}
