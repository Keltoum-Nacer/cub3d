#include "../include_files/cub3d.h"

void    init_textures(t_data *data)
{
    char *names[4];

    names[0] = data->map.south;
    names[1] = data->map.north;
    names[2] = data->map.east;
    names[3] = data->map.west;
    int i = 0;
    while(i < 4)
    {
        data->textures[i].text_mlx.image = mlx_xpm_file_to_image(data->mlx.mlx, names[i], &data->text.width, &data->text.height);
        if (!data->textures[i].text_mlx.image)
        {
            printf("the image cannot be loaded successfully\n");
            return;
        }
        data->textures[i].text_mlx.image_addr = mlx_get_data_addr(data->textures[i].text_mlx.image, &data->textures[i].text_mlx.bits_per_pixel, &data->textures[i].text_mlx.line_length, &data->textures[i].text_mlx.endian);
        i++;
    }
}

void init_mlx(t_data *data)
{
   
    data->mlx.mlx = mlx_init();
    if (!data->mlx.mlx)
        return;
    data->mlx.image = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
    data->mlx.window = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "Our Cub3D");
    if (!data->mlx.window)
        return;
    init_textures(data);
}

void    init_data(t_map map, t_data *data)
{
    data->map = map;
    data->map.p.p_y *= WALL_DIM ;
    data->map.p.p_x *= WALL_DIM;
    if (map.p.p_name == 'N')
        data->map.p.angle = (3 * PI) / 2;
    if (map.p.p_name == 'W')
        data->map.p.angle = PI;
    if (map.p.p_name == 'S')
        data->map.p.angle = PI / 2;
    if (map.p.p_name == 'E')
        data->map.p.angle = 0;
    init_mlx(data);
}
