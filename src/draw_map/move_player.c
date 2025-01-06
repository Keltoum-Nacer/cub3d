#include "../include_file/cub3d.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}
void    validate_move(t_data *data, double new_x, double new_y)
{
    if (data->map.map[(int)(data->map.p.p_y/ WALL_DIM)][(int)((new_x+4)/ WALL_DIM)] != '1')
        data->map.p.p_x = new_x;
    if (data->map.map[(int)((new_y+4)/ WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] != '1')
        data->map.p.p_y = new_y;
}
int handle_key(int keycode, t_data *data)
{
    data->key = keycode;
    if (keycode == ESC)
        return (mlx_loop_end(data->mlx.mlx), 1);
    double angle = data->map.p.angle;
    if (keycode == KEY_W)
    {
        double new_x = (data->map.p.p_x + SPEED * cos(angle)) ;
        double new_y = (data->map.p.p_y + SPEED * sin(angle)) ;
        validate_move(data, new_x, new_y);
    }

    if (keycode == KEY_S)
    {
        double new_x= (data->map.p.p_x - SPEED * cos(angle)) ;
        double new_y = (data->map.p.p_y - SPEED * sin(angle));
        validate_move(data, new_x, new_y);
    }
    // if (keycode == KEY_A)
    // {
    //     double new_x = data->map.p.p_x - SPEED * cos(angle + PI / 2);
    //     double new_y = data->map.p.p_y - SPEED * sin(angle + PI / 2);
    //     validate_move(data, new_x, new_y);
    // }
    // if (keycode == KEY_D)
    // {
    //     double new_x = data->map.p.p_x + SPEED * cos(angle + PI / 2);
    //     double new_y = data->map.p.p_y + SPEED * sin(angle + PI / 2);
    //     validate_move(data, new_x, new_y);
    // }
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
    if (keycode == OPEN)
        data->map.open_door = 1;
    return (move_player(data), 1);
}
