#include "../../include_files/cub3d_bonus.h"

int	check_wall_door(t_point p0, double alpha, t_data *data, int i)
{
	t_point	player;

	player.x_ind = data->map.p.p_x;
	player.y_ind = data->map.p.p_y;
	if (data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind / WALL_DIM)]
		&& data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind
			/ WALL_DIM)] == '1')
	{
		data->map.is_door = 0;
		data->map.p.wall_dist = calculate_distance(p0, player);
		render_wall_projection(p0, data, alpha, i);
		return (1);
	}
	if (data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind / WALL_DIM)]
		&& data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind
			/ WALL_DIM)] == 'D' && !data->map.open_door)
	{
		data->map.is_door = 1;
		data->map.p.wall_dist = calculate_distance(p0, player);
		render_wall_projection(p0, data, alpha, i);
		return (1);
	}
	return (0);
}

void	build_wall(t_point p0, int start, int end, t_data *data)
{
	int	i;

	i = 0;
	while (i < start)
	{
		my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.c_color);
		i++;
	}
	i = build_texters(data, i, end, p0);
	while (i < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.f_color);
		i++;
	}
}

void	render_wall_projection(t_point p0, t_data *data, double alpha, int i)
{
	double	dis_to_proj;
	double	precise_dist;
	int		start;
	int		end;

	alpha = normalize_angle(alpha);
	data->map.p.ray_angle = alpha;
	precise_dist = data->map.p.wall_dist * cos(alpha - data->map.p.angle);
	dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(FOV / 2));
	data->map.p.wall_height = round((dis_to_proj / precise_dist) * WALL_DIM);
	start = (WIN_HEIGHT / 2) - (int)(data->map.p.wall_height / 2);
	end = (WIN_HEIGHT / 2) + (int)(data->map.p.wall_height / 2);
	data->map.p.hit_x = p0.x_ind;
	data->map.p.hit_y = p0.y_ind;
	p0.x_ind = i;
	build_wall(p0, start, end, data);
}
