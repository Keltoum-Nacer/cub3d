#include "../include_files/cub3d_bonus.h"

int ft_close(t_data *cub)
{
    mlx_destroy_image(cub->mlx.mlx, cub->mlx.image);
	mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
	exit(0);
}
int mouse_move(int x, int y, t_data *data)
{
    (void)y;
   static int last_x = -1; // Uninitialized state

    // if (last_x == -1)
    //     mlx_mouse_get_pos(data->mlx.mlx, data->mlx.window, &last_x, NULL);

    if (x > last_x)
    {
        data->map.p.angle += 0.005;
        if (data->map.p.angle > 2 * PI)
            data->map.p.angle -= 2 * PI;
    }
    else if (x < last_x)
    {
        data->map.p.angle -=  0.005;
        if (data->map.p.angle < 0)
            data->map.p.angle += 2 * PI;
    }
    //mlx_mouse_show(data->mlx.mlx, data->mlx.window);
    last_x = x;

    return(move_player(data), 1);
}

void    hook_functions(t_data *data)
{
    mlx_hook(data->mlx.window, 17, 0, ft_close, data);
    mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);
    mlx_hook(data->mlx.window, 6, 1L << 6, mouse_move, data);
}
