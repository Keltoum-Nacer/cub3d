#include "../include_files/cub3d_bonus.h"

void player(t_data *data)
{
    int i;
    int j;
    double  scale_H;
    double  scale_W;
    double  x;
    double  y;
    int     color;

    i = 0;
    data->anim.player = ft_strdup("textures/simonkraft/player2.xpm");
    data->anim.text_mlx.image = mlx_xpm_file_to_image(data->mlx.mlx, data->anim.player, &data->anim.width, &data->anim.height);
        if (!data->anim.text_mlx.image)
        {
            printf("the image cannot be loaded successfully\n");
            return;
        }
        data->anim.text_mlx.image_addr = mlx_get_data_addr(data->anim.text_mlx.image, &data->anim.text_mlx.bits_per_pixel, &data->anim.text_mlx.line_length, &data->anim.text_mlx.endian);
    scale_H = WIN_HEIGHT / (double) data->anim.height;
    scale_W = WIN_WIDTH / (double) data->anim.width;
    while(i < WIN_HEIGHT)
    {
        j = 0;
        while(j < WIN_WIDTH)
        {
            x = i / scale_H;
            y = j / scale_W;
            color =  *(int *)(data->anim.text_mlx.image_addr +
                        ((int)x * data->anim.text_mlx.line_length) +
                        ((int)y* (data->anim.text_mlx.bits_per_pixel / 8)));
            my_mlx_pixel_put(&data->mlx, j, i, color);
            j +=2;
        }
        i++;
    }
}
