#include "../../include_files/cub3d_bonus.h"

void move_player(t_data *data)
{
	data->mlx.image_addr = mlx_get_data_addr(data->mlx.image,
											 &data->mlx.bits_per_pixel, &data->mlx.line_length,
											 &data->mlx.endian);
	mlx_do_sync(data->mlx.mlx);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0,
							0);
}
void validate_move(t_data *data, double new_x, double new_y, int flag_x,
				   int flag_y)
{
	if (data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)] != '1' && data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)])
	{
		if (data->map.map[(int)(data->map.p.p_y / WALL_DIM)][(int)((new_x) / WALL_DIM)] == 'D' && !data->map.open_door)
			return;
		data->map.p.p_x = new_x - flag_x;
	}
	if (data->map.map[(int)(new_y / WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] && data->map.map[(int)(new_y / WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] != '1')
	{
		if (data->map.map[(int)(new_y / WALL_DIM)][(int)(data->map.p.p_x / WALL_DIM)] == 'D' && !data->map.open_door)
			return;
		data->map.p.p_y = new_y - flag_y;
	}
}

void move_leftright(int keycode, t_data *data)
{
	double new_x;
	double new_y;

	if (keycode == KEY_A)
	{
		new_x = data->map.p.p_x - SPEED * cos(data->map.p.angle + PI / 2) - CO * cos(data->map.p.angle + PI / 2);
		new_y = data->map.p.p_y - SPEED * sin(data->map.p.angle + PI / 2) - CO * sin(data->map.p.angle + PI / 2);
		validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle + PI / 2),
					  -CO * sin(data->map.p.angle + PI / 2));
	}
	if (keycode == KEY_D)
	{
		new_x = data->map.p.p_x + SPEED * cos(data->map.p.angle + PI / 2) + CO * cos(data->map.p.angle + PI / 2);
		new_y = data->map.p.p_y + SPEED * sin(data->map.p.angle + PI / 2) + CO * sin(data->map.p.angle + PI / 2);
		validate_move(data, new_x, new_y, CO * cos(data->map.p.angle + PI / 2),
					  CO * sin(data->map.p.angle + PI / 2));
	}
}

void move_updown(int keycode, t_data *data)
{
	double new_x;
	double new_y;

	if (keycode == KEY_W)
	{
		new_x = (data->map.p.p_x + SPEED * cos(data->map.p.angle)) + CO * cos(data->map.p.angle);
		new_y = (data->map.p.p_y + SPEED * sin(data->map.p.angle)) + CO * sin(data->map.p.angle);
		validate_move(data, new_x, new_y, CO * cos(data->map.p.angle), CO * sin(data->map.p.angle));
	}
	if (keycode == KEY_S)
	{
		new_x = (data->map.p.p_x - SPEED * cos(data->map.p.angle)) - CO * cos(data->map.p.angle);
		new_y = (data->map.p.p_y - SPEED * sin(data->map.p.angle)) - CO * sin(data->map.p.angle);
		validate_move(data, new_x, new_y, -CO * cos(data->map.p.angle), -CO * sin(data->map.p.angle));
	}
}

void rot(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->map.p.angle += 0.10;
	if (keycode == KEY_RIGHT)
		data->map.p.angle -= 0.10;
	data->map.p.angle = normalize_angle(data->map.p.angle);
}
int handle_key(int keycode, t_data *data)
{
	if (keycode == ESC)
		return (ft_close(data), 1);
	if (keycode == KEY_W || keycode == KEY_S)
		move_updown(keycode, data);
	if (keycode == KEY_A || keycode == KEY_D)
		move_leftright(keycode, data);
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		rot(keycode, data);
	if (keycode == OPEN)
		data->map.open_door = 1;
	if (keycode == CLOSE && data->map.map[(int)(data->map.p.p_y / WALL_DIM)] [(int)(data->map.p.p_x / WALL_DIM)] != 'D')
	{
		data->map.open_door = 0;
		move_player(data);
	}
	if (keycode == SPC)
		data->text.hidden = 0;
	if (keycode == KEY_M && data->flag % 2)
		return (data->wall = 1, draw_anim(data), 1);
	if (keycode == KEY_N && data->flag % 2)
		return (data->wall = 0, draw_anim(data), 1);
	if (keycode == KEY_G)
		data->flag++;
	return (move_player(data), 1);
}
