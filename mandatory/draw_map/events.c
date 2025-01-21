#include "../../include_files/cub3d.h"

int	ft_close(t_data *cub)
{
	destroy_all(*cub);
	exit(0);
}

void	hook_functions(t_data *data)
{
	mlx_hook(data->mlx.window, 17, 0, ft_close, data);
	mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);
}

double	calculate_distance(t_point p0, t_point p1)
{
	return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind,
				2.)));
}

int	draw_map(t_data *data)
{
	draw_raycasting(data);
	return (0);
}

void	move_player(t_data *data)
{
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.end);
	draw_map(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.img, 0,
		0);
}
