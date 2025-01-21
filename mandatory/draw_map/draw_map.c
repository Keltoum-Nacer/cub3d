#include "../../include_files/cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (y * data->line_len) + (x * (data->bpp / 8));
	*((unsigned int *)(data->addr + offset)) = color;
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

double	degree_to_rad(float fov)
{
	double	rad;

	rad = fov * PI / DEGREE_180;
	return (rad);
}

void	draw_raycasting(t_data *data)
{
	double	fov;
	double	angle_step;
	double	ray_angle;
	t_point	x;
	int		i;

	fov = degree_to_rad(FOV);
	angle_step = fov / RAYS;
	ray_angle = data->map.p.angle - (fov / 2);
	x.x_ind = data->map.p.p_x;
	x.y_ind = data->map.p.p_y;
	i = 0;
	while (i < RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		bresenham(x, ray_angle, data, i);
		ray_angle += angle_step;
		i++;
	}
}
