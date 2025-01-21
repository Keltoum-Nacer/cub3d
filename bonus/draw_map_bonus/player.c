#include "../include_files/cub3d_bonus.h"

int	animation_player(t_data *data)
{
	int		i;
	char	path[256];

	i = 0;
	while (i < 27)
	{
		data->mlx.image_addr = mlx_get_data_addr(data->mlx.image,
				&data->mlx.bits_per_pixel, &data->mlx.line_length,
				&data->mlx.endian);
		mlx_do_sync(data->mlx.mlx);
		draw_raycasting(data);
		snprintf(path, sizeof(path), PATH_PLAYER, i + 1);
		if (i == 25 && data->wall)
			data->flag_weast = 1;
		else if (i == 25 && !data->wall)
			data->flag_east = 1;
		draw_player(data, path);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
			data->mlx.image, 0, 0);
		rendring_minimap(data);
		usleep(40000);
		i++;
	}
	return (0);
}

void	put_player(t_data *data, double x, double y)
{
	double	offset_x;
	double	offset_y;
	int		color;

	offset_x = 0;
	while (offset_x < data->player.img_width)
	{
		offset_y = 0;
		while (offset_y < data->player.img_height)
		{
			color = *(int *)(data->player.image_addr + (int)(offset_y
						* data->player.line_length + offset_x
						* (data->player.bits_per_pixel / 8)));
			if (color != TRANSPARENT_COLOR)
				my_mlx_pixel_put(&data->mlx, x + offset_x, y + offset_y, color);
			offset_y++;
		}
		offset_x++;
	}
}

void	draw_player(t_data *data, char *name)
{
	double	y;
	double	x;

	data->player.image = mlx_xpm_file_to_image(data->mlx.mlx, name,
			&data->player.img_width, &data->player.img_height);
	if (!data->player.image)
		return ;
	y = WIN_HEIGHT - SCALE_YP - data->player.img_height;
	data->player.image_addr = mlx_get_data_addr(data->player.image,
			&data->player.bits_per_pixel, &data->player.line_length,
			&data->player.endian);
	if (data->flag % 2)
		x = 175;
	else
		x = 370;
	put_player(data, x, y);
	mlx_destroy_image(data->mlx.mlx, data->player.image);
}

void	mini_player(int x, int y, int color, t_mlx *mlx)
{
	double	r;
	double	i;
	double	angle;
	double	x1;
	double	y1;

	r = 3.5;
	i = 0;
	while (i <= r)
	{
		angle = 0;
		while (angle < DEGREE_360)
		{
			x1 = i * cos(angle * PI / DEGREE_180);
			y1 = i * sin(angle * PI / DEGREE_180);
			if (i >= 3.3)
				my_mlx_pixel_put(mlx, x * MINI_GRID + x1, y * MINI_GRID + y1,
					PLAYER_MINI);
			else
				my_mlx_pixel_put(mlx, x * MINI_GRID + x1, y * MINI_GRID + y1,
					color);
			angle += 0.1;
		}
		i += 0.1;
	}
}

void	move_player(t_data *data)
{
	data->mlx.image_addr = mlx_get_data_addr(data->mlx.image,
			&data->mlx.bits_per_pixel, &data->mlx.line_length,
			&data->mlx.endian);
	mlx_do_sync(data->mlx.mlx);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0,
		0);
}
