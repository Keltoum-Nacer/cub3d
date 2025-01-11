#include "../include_files/cub3d_bonus.h"

void player(t_data *data)
{
    int i;
    int j;
    double  scale_H;
    double  scale_W;
    int     color;

    i = 0;
    data->text.player = ft_strdup("textures/simonkraft/player.xpm");
    data->text.text_mlx.image = mlx_xpm_file_to_image(data->mlx.mlx, data->text.player, &data->text.width, &data->text.height);
        if (!data->text.text_mlx.image)
        {
            printf("the image cannot be loaded successfully\n");
            return;
        }
        data->text.text_mlx.image_addr = mlx_get_data_addr(data->text.text_mlx.image, &data->text.text_mlx.bits_per_pixel, &data->text.text_mlx.line_length, &data->text.text_mlx.endian);
    scale_H = WIN_HEIGHT / (double) data->textures[5].height;
    scale_W = WIN_WIDTH / (double) data->textures[5].width;
    while(i < WIN_HEIGHT)
    {
        j = 0;
        while(j < WIN_WIDTH)
        {
            color =  *(int *)(data->text.text_mlx.image_addr +
                        ((int)(i / scale_H) * data->text.text_mlx.line_length) +
                        ((int)(j / scale_W)* (data->text.text_mlx.bits_per_pixel / 8)));
            my_mlx_pixel_put(&data->mlx, i, j, color);
            j++;
        }
        i++;
    }
}