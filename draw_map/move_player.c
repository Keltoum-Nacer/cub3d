#include "../include_file/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    // if (data->map.map[(int)data->map.p.p_y / 64][(int)data->map.p.p_x / 64] == '1' )
    //     return;
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}


int no_event(t_data *data)
{
    float x;
    float y;

    x = data->map.p.p_x;
    y = data->map.p.p_y;

    if (data->key == KEY_W)
        y -= 64;
    if(data->key == KEY_S)
        y += 64;
    if(data->key == KEY_D)
        x -= 64;
    if (data->key == KEY_A)
        x += 64;
    if(data->map.map[(int)y / 64] [(int)x / 64] == '1' || !data->map.map[(int)y / 64][(int)x / 64])
        return(SUCCESS);
    return(FAILURE);
}

int handle_key(int keycode, t_data *data)
{
    data->key = keycode;
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    if (keycode == KEY_W && !no_event(data))
        data->map.p.p_y -= 64;
    if (keycode == KEY_S && !no_event(data))
        data->map.p.p_y += 64;
    if (keycode == KEY_D && !no_event(data))
        data->map.p.p_x -= 64;
    if (keycode == KEY_A && !no_event(data))
        data->map.p.p_x += 64;
    if (keycode == KEY_LEFT)
        data->map.p.angle += 1;
    if (keycode == KEY_RIGHT)
        data->map.p.angle -= 1;
    return (move_player(data), 1);
}



