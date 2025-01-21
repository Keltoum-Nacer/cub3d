#include "../include_files/cub3d_bonus.h"

void	render_raycasting_minimap(t_data *data)
{
	double	fov;
	double	angle_step;
	double	ray_angle;
	t_point	x;

	fov = degree_to_rad(FOV);
	angle_step = fov / NUM_RAYS;
	ray_angle = data->map.p.angle - (fov / 2);
	x.x_ind = 6.1 * MINI_GRID;
	x.y_ind = 6.1 * MINI_GRID;
	ray_angle = normalize_angle(ray_angle);
	bresenham_mini_map(x, ray_angle, data);
	ray_angle += angle_step;
	bresenham_mini_map(x, ray_angle, data);
	ray_angle += FOV * PI / DEGREE_180 - angle_step;
	ray_angle = normalize_angle(ray_angle);
	bresenham_mini_map(x, ray_angle, data);
	bresenham_mini_map(x, ray_angle - angle_step, data);
	ray_angle += angle_step;
}

void	draw_pixels_mini_map(int i, int j, int color, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < MINI_GRID)
	{
		y = 0;
		while (y < MINI_GRID)
		{
			my_mlx_pixel_put(mlx, i + x, j + y, color);
			y++;
		}
		x++;
	}
}

void	draw_minimap(int i, int j, t_point center, t_data *data)
{
	if (data->map.map[i][j] == '1')
		draw_pixels_mini_map(((j - center.x_ind) + VIEW_RADIUS) * 12, ((i
					- center.y_ind) + VIEW_RADIUS) * 12, COL_WALL, &data->mlx);
	else if (data->map.map[i][j] == ' ')
		draw_pixels_mini_map(((j - center.x_ind) + VIEW_RADIUS) * 12, ((i
					- center.y_ind) + VIEW_RADIUS) * 12, COL_SP, &data->mlx);
	else if (data->map.map[i][j] == 'D' && !data->map.open_door)
		draw_pixels_mini_map(((j - center.x_ind) + VIEW_RADIUS) * 12, ((i
					- center.y_ind) + VIEW_RADIUS) * 12, COL_D, &data->mlx);
	else
		draw_pixels_mini_map(((j - center.x_ind) + VIEW_RADIUS) * 12, ((i
					- center.y_ind) + VIEW_RADIUS) * 12, COL_0, &data->mlx);
}

void	draw_mini_map(t_data *data, t_point center)
{
	double	dx;
	double	dy;
	double	dist_squared;
	int		i;
	int		j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			dx = j - center.x_ind;
			dy = i - center.y_ind;
			dist_squared = dx * dx + dy * dy;
			if (dist_squared <= VIEW_RADIUS * VIEW_RADIUS)
				draw_minimap(i, j, center, data);
			j++;
		}
		i++;
	}
}

void	rendring_minimap(t_data *data)
{
	t_point	center;

	center.x_ind = (data->map.p.p_x / WALL_DIM) + 0.2;
	center.y_ind = (data->map.p.p_y / WALL_DIM) + 0.2;
	draw_mini_map(data, center);
	mini_player(6.5, 6.5, COL_SP, &data->mlx);
	render_raycasting_minimap(data);
}
