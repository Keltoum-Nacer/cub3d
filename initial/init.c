#include "../include_file/cub3d.h"

void init_mlx(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return;
    mlx->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx->image_addr = mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
    mlx->window = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Our Cub3D");
    if (!mlx->window)
        return;
}

void init_data(t_map map, t_data *data)
{
    data->map = map;
    data->map.p.p_y *= 64 ;
    data->map.p.p_x *= 64;
    if (map.p.p_name == 'N')
        data->map.p.angle = 270;
    if (map.p.p_name == 'W')
        data->map.p.angle = 180;
    if (map.p.p_name == 'S')
        data->map.p.angle = 90;
    if (map.p.p_name == 'E')
        data->map.p.angle = 0;
    init_mlx(&data->mlx);
}
