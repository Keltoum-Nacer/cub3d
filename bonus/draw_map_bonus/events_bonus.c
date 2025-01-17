#include "../include_files/cub3d_bonus.h"

int ft_close(t_data *cub)
{
    char *end;

    end = ft_strdup("textures/simonkraft/end.xpm");
    cub->text.end.image = mlx_xpm_file_to_image(cub->mlx.mlx, end, &cub->text.width, &cub->text.height);
    if (!cub->text.end.image)
    {
        printf("the image cannot be loaded successfully\n");
        return (0);
    }
    mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.window, cub->text.end.image, 0, 0);
    mlx_do_sync(cub->mlx.mlx);
    sleep(2);
    mlx_destroy_image(cub->mlx.mlx, cub->mlx.image);
    mlx_destroy_window(cub->mlx.mlx, cub->mlx.window);
    exit(0);
}
int mouse_move(int x, int y, t_data *data)
{
    (void)y;
    static int last_x = WIN_WIDTH / 2;
    if (x > last_x)
    {
        data->map.p.angle += 0.03;
        data->map.p.angle = normalize_angle(data->map.p.angle);
    }
    if (x < last_x)
    {
        data->map.p.angle -= 0.03;
        data->map.p.angle = normalize_angle(data->map.p.angle);
    }
    last_x = x;
    return (move_player(data), 1);
}

void hook_functions(t_data *data)
{
    mlx_hook(data->mlx.window, 17, 0, ft_close, data);
    mlx_hook(data->mlx.window, 2, 1L << 0, handle_key, data);
    mlx_hook(data->mlx.window, 6, 1L << 6, mouse_move, data);
}
