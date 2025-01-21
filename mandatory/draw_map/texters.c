#include "../include_files/cub3d.h"

unsigned int	darkness(unsigned int color, double distance, int max_distance)
{
	double	dark_factor;
	int		r;
	int		g;
	int		b;

	dark_factor = 1 - (distance / max_distance);
	if (dark_factor < 0)
		dark_factor = 0;
	if (dark_factor > 1)
		dark_factor = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * dark_factor;
	g = g * dark_factor;
	b = b * dark_factor;
	return ((r << 16) | (g << 8) | b);
}

int	check_texture(t_data *data)
{
	if (!data->map.p.flag)
	{
		data->map.p.offset_x = data->text.width - fmod(data->map.p.hit_x,
				WALL_DIM) / WALL_DIM * data->text.width;
		if (data->map.p.ray_angle > 0 && data->map.p.ray_angle < PI)
			return (data->texts[0].name = data->map.south, 0);
		else
			return (data->texts[1].name = data->map.north, 1);
	}
	else
	{
		data->map.p.offset_x = fmod(data->map.p.hit_y, WALL_DIM) / WALL_DIM
			* data->text.width;
		if (data->map.p.ray_angle > (3 * PI) / 2 || data->map.p.ray_angle < PI
			/ 2)
			return (data->texts[2].name = data->map.east, 2);
		else
			return (data->texts[3].name = data->map.west, 3);
	}
	return (0);
}

int	draw_textures(t_data *data, int i, int end, t_point p0)
{
	int		color;
	int		j;
	double	distance_from_top;
	double	texture_offset_y;

	j = check_texture(data);
	while (i < end)
	{
		distance_from_top = i + (data->map.p.wall_height / 2) - (HEIGHT / 2);
		texture_offset_y = distance_from_top * ((double)data->text.height
				/ data->map.p.wall_height);
		if (data->map.p.offset_x <= data->text.width
			&& data->map.p.offset_x >= 0
			&& texture_offset_y <= data->text.height && texture_offset_y >= 0)
		{
			color = *(int *)(data->texts[j].t.addr + ((int)texture_offset_y
						* data->texts[j].t.line_len)
					+ ((int)data->map.p.offset_x * (data->texts[j].t.bpp / 8)));
		}
		my_mlx_pixel_put(&data->mlx, p0.x_ind, i, color);
		i++;
	}
	return (i);
}

void	draw_wall(t_point p0, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while (i < start)
	{
		my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.c_color);
		i++;
	}
	i = draw_textures(data, i, end, p0);
	while (i < HEIGHT)
	{
		my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.f_color);
		i++;
	}
}
