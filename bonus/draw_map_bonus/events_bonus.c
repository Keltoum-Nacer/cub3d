#include "../include_files/cub3d_bonus.h"

int ft_close(t_data *cub)
{
    mlx_destroy_image(cub->mlx.mlx, cub->mlx.image);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	exit(0);
}

void    hook_functions(t_data *data)
{
    mlx_hook(data->mlx.window, 17, 0, ft_close, data);
    mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);

}
