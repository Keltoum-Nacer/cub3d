#include "../include_files/cub3d.h"

void	validate_move(t_data *data, int flag_x, int flag_y)
{
	if (data->map.map[(int)((data->new_y) / WALL_DIM)][(int)((data->new_x)
			/ WALL_DIM)] != '1')
	{
		data->map.p.p_x = data->new_x - flag_x;
		data->map.p.p_y = data->new_y - flag_y;
	}
}

void	move_up_down(t_data *data, int keycode)
{
	if (keycode == KEY_W)
	{
		data->new_x = (data->map.p.p_x + SPEED * cos(data->map.p.angle)) + CO
			* cos(data->map.p.angle);
		data->new_y = (data->map.p.p_y + SPEED * sin(data->map.p.angle)) + CO
			* sin(data->map.p.angle);
		validate_move(data, CO * cos(data->map.p.angle), CO
			* sin(data->map.p.angle));
	}
	else
	{
		data->new_x = (data->map.p.p_x - SPEED * cos(data->map.p.angle)) - CO
			* cos(data->map.p.angle);
		data->new_y = (data->map.p.p_y - SPEED * sin(data->map.p.angle)) - CO
			* sin(data->map.p.angle);
		validate_move(data, -CO * cos(data->map.p.angle), -CO
			* sin(data->map.p.angle));
	}
	move_player(data);
}

void	move_left_right(t_data *data, int keycode)
{
	if (keycode == KEY_A)
	{
		data->new_x = data->map.p.p_x - SPEED * cos(data->map.p.angle + PI / 2)
			- CO * cos(data->map.p.angle + PI / 2);
		data->new_y = data->map.p.p_y - SPEED * sin(data->map.p.angle + PI / 2)
			- CO * sin(data->map.p.angle + PI / 2);
		validate_move(data, -CO * cos(data->map.p.angle + PI / 2), -CO
			* sin(data->map.p.angle + PI / 2));
	}
	else
	{
		data->new_x = data->map.p.p_x + SPEED * cos(data->map.p.angle + PI / 2)
			+ CO * cos(data->map.p.angle + PI / 2);
		data->new_y = data->map.p.p_y + SPEED * sin(data->map.p.angle + PI / 2)
			+ CO * sin(data->map.p.angle + PI / 2);
		validate_move(data, CO * cos(data->map.p.angle + PI / 2), CO
			* sin(data->map.p.angle + PI / 2));
	}
	move_player(data);
}

void	rot(t_data *data, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		data->map.p.angle += 0.10;
		data->map.p.angle = normalize_angle(data->map.p.angle);
	}
	else
	{
		data->map.p.angle -= 0.10;
		data->map.p.angle = normalize_angle(data->map.p.angle);
	}
	move_player(data);
}

int	handle_key(int keycode, t_data *data)
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
