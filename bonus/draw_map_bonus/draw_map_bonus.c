#include "../include_files/cub3d_bonus.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	*((unsigned int *)(data->image_addr + offset)) = color;
}

void	draw_pixels(int i, int j, int color, t_mlx *mlx)
{
	int	ver;
	int	hor;

	ver = 0;
	hor = 0;
	while (ver < WALL_DIM)
	{
		hor = 0;
		while (hor < WALL_DIM)
		{
			my_mlx_pixel_put(mlx, WALL_DIM * i + hor, WALL_DIM * j + ver,
				color);
			hor++;
		}
		ver++;
	}
}

void	draw_raycasting(t_data *data)
{
	double	fov;
	double	angle_step;
	double	ray_angle;
	t_point	x;
	int		i;

	fov = degree_to_rad(FOV);
	angle_step = fov / NUM_RAYS;
	ray_angle = data->map.p.angle - (fov / 2);
	x.x_ind = data->map.p.p_x;
	x.y_ind = data->map.p.p_y;
	i = 0;
	while (i < NUM_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		bresenham(x, ray_angle, data, i);
		ray_angle += angle_step;
		i++;
	}
}

int	draw_map(t_data *data)
{
	draw_raycasting(data);
	if (data->flag % 2)
		draw_player(data, "textures/anim_player/player1.xpm");
	else
		draw_player(data, "textures/simonkraft/player2_resize.xpm");
	rendring_minimap(data);
	return (0);
}
