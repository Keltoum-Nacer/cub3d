#include "../include_file/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    if (data->map.map[(int)data->map.p.p_y / 30][(int)data->map.p.p_x / 30] == '1')
        return ;
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}
int handle_key(int keycode, t_data *data)
{
    printf(">>>%d\n", keycode);
    if(keycode == ESC)
        return(mlx_loop_end(data->mlx.mlx), 1);
    if (keycode == KEY_W)
    {
        data->map.p.p_y = data->map.p.p_y - 5;
        return (move_player(data), 1);
    }
    if (keycode == KEY_D)
    {
        data->map.p.p_x = data->map.p.p_x + 5;
        return (move_player(data), 1);
    }
    if (keycode == KEY_A)
    {
        data->map.p.p_x = data->map.p.p_x - 5;
        return (move_player(data), 1);
    }
    if (keycode == KEY_S)
    {
        data->map.p.p_y = data->map.p.p_y + 5;
        return (move_player(data), 1);
    }
    return (0);
}
