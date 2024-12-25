#include "../include_file/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    // if (data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64] == '1' )
    //     return;
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}


int handle_key(int keycode, t_data *data)
{
    data->key = keycode;
    double tmp;
    tmp = data->map.p.p_x;
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    double angle = data->map.p.angle_orig * PI / 180 + data->map.p.angle * PI / 180;

    if (angle > 2 * PI)
        angle -= 2 * PI;
    if (angle < 0)
        angle += 2 * PI;

    if (keycode == KEY_W)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)(data->map.p.p_x + SPEED * cos(angle)) / 64] != '1')
            data->map.p.p_x += SPEED * cos(angle);
        if (data->map.map[(int)(data->map.p.p_y + SPEED * sin(angle)) / 64][(int)tmp / 64] != '1')
            data->map.p.p_y += SPEED * sin(angle);
    }

    if (keycode == KEY_S)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)(data->map.p.p_x - SPEED * cos(angle)) / 64] != '1')
            data->map.p.p_x -= SPEED * cos(angle);
        if (data->map.map[(int)(data->map.p.p_y - SPEED * sin(angle)) / 64][(int)tmp / 64] != '1')
            data->map.p.p_y -= SPEED * sin(angle);
    }
    if (keycode == KEY_A)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)(data->map.p.p_x - SPEED * cos(angle + PI / 2)) / 64] != '1')
            data->map.p.p_x -= SPEED * cos(angle + PI / 2);
        if (data->map.map[(int)(data->map.p.p_y - SPEED * sin(angle + PI / 2)) / 64][(int)tmp / 64] != '1')
            data->map.p.p_y -= SPEED * sin(angle + PI / 2);
    }
    if (keycode == KEY_D)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)(data->map.p.p_x + SPEED * cos(angle + PI / 2))] != '1')
            data->map.p.p_x += SPEED * cos(angle + PI / 2);
        if (data->map.map[(int)(data->map.p.p_y + SPEED * sin(angle + PI / 2)) / 64][(int)tmp / 64] != '1')
            data->map.p.p_y += SPEED * sin(angle + PI / 2);
    }
    if (keycode == KEY_LEFT)
    {
        data->map.p.angle += 1;
        data->map.p.angle_orig += 1;
        if (data->map.p.angle > 360)
            data->map.p.angle -= 360;
        if (data->map.p.angle_orig > 360)
            data->map.p.angle_orig -= 360;
    }
    if (keycode == KEY_RIGHT)
    {
        data->map.p.angle -= 1;
        data->map.p.angle_orig -= 1;
        if (data->map.p.angle < 0)
            data->map.p.angle += 360;
        if (data->map.p.angle_orig < 0)
            data->map.p.angle_orig += 360;
    }
    return (move_player(data), 1);
}
