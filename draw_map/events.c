#include "../include_file/cub3d.h"

int ft_close(t_data *cub)
{
        mlx_loop_end(cub->mlx.mlx);
	    return(0);
}

void    hook_functions(t_data *data)
{
    mlx_hook(data->mlx.window, 17, 0, ft_close, data);
    mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);

}
