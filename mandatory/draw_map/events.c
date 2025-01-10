#include "../../include_files/cub3d.h"

int ft_close(t_data *cub)
{
    destroy_all(*cub);
	exit(0);
}

void    hook_functions(t_data *data)
{
    mlx_hook(data->mlx.window, 17, 0, ft_close, data);
    mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);

}
