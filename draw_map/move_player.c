#include "../include_file/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    // printf("--->%f--->%f\n", data->map.p.p_y , data->map.p.p_x);
    if (data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64] == '1' ) 
        return;
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}



int handle_key(int keycode, t_data *data)
{
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    if (keycode == KEY_W)
    {
        if (!data->map.p.p_y)
            return (1);
        data->map.p.p_y = data->map.p.p_y - 1;
        return (move_player(data), 1);
    }
    if (keycode == KEY_D)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64] == '1' || !data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64])
            return (1);
        data->map.p.p_x = data->map.p.p_x  +1;
        return (move_player(data), 1);
    }
    if (keycode == KEY_A)
    {
        if (!data->map.p.p_y)
            return (1);
        data->map.p.p_x = data->map.p.p_x - 1;
        return (move_player(data), 1);
    }
    if (keycode == KEY_S)
    {
        if (data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64] == '1' || !data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64])
            return (1);
        data->map.p.p_y = data->map.p.p_y +1;
        return (move_player(data), 1);
    }
    if (keycode == KEY_LEFT)
    {
        data->map.p.angle = data->map.p.angle + 1;
        return (move_player(data), 1);
    }
    if (keycode == KEY_RIGHT)
    {
        data->map.p.angle = data->map.p.angle - 1;
        return (move_player(data), 1);
    }
    return (0);
}



