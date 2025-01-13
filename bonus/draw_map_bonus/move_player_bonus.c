#include "../../include_files/cub3d_bonus.h"

void move_player(t_data *data)
{
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    mlx_do_sync(data->mlx.mlx);
    draw_map(data);
    mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}
void validate_move(t_data *data, double new_x, double new_y, int flag_x, int flag_y)
{
        // printf("=============%f++++++++++++++++%f\n", new_x, new_y);
        // printf("***************************%c\n",data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)]);
    if (data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)] == '0' || data->map.open_door || data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)] == data->map.p.p_name)
    {
        // printf(">>>>>%c\n", data->map.p.p_name);
        data->map.p.p_x = new_x - flag_x;
    }
    if (data->map.map[(int)(new_y / WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] == '0' || data->map.open_door || data->map.map[(int)(new_y / WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] == data->map.p.p_name)
    {
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
        double new_x = (data->map.p.p_x + SPEED * cos(angle)) + CO * cos(data->map.p.angle);
        double new_y = (data->map.p.p_y + SPEED * sin(angle)) + CO * sin(data->map.p.angle);
        validate_move(data, new_x, new_y, CO * cos(data->map.p.angle), CO * sin(data->map.p.angle));
    }

    if (keycode == KEY_S)
    {
        double new_x = (data->map.p.p_x - SPEED * cos(data->map.p.angle)) - CO * cos(data->map.p.angle);
        double new_y = (data->map.p.p_y - SPEED * sin(data->map.p.angle)) - CO * sin(data->map.p.angle);
        validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle), -CO * sin(data->map.p.angle));
    }
    if (keycode == KEY_A)
    {
        double new_x = data->map.p.p_x - SPEED * cos(data->map.p.angle + PI / 2) - CO * cos(data->map.p.angle + PI / 2);
        double new_y = data->map.p.p_y - SPEED * sin(data->map.p.angle + PI / 2) - CO * sin(data->map.p.angle + PI / 2);
        validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle + PI / 2), -CO * sin(data->map.p.angle + PI / 2));
    }
    if (keycode == KEY_D)
    {
        double new_x = data->map.p.p_x + SPEED * cos(data->map.p.angle + PI / 2) + CO * cos(data->map.p.angle + PI / 2);
        double new_y = data->map.p.p_y + SPEED * sin(data->map.p.angle + PI / 2) + CO * sin(data->map.p.angle + PI / 2);
        validate_move(data, new_x, new_y, CO * cos(data->map.p.angle + PI / 2), CO * sin(data->map.p.angle + PI / 2));
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
    if (keycode == OPEN)
        data->map.open_door = 1;
    if (keycode == CLOSE)
        data->map.open_door = 0;
    if (keycode == SPC)
        data->text.hidden = 0;
    return (move_player(data), 1);
}