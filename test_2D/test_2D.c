#include "../include_file/cub3d.h"

void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= WIN_HEIGHT || y < 0 || y >= WIN_WIDTH)
		return ;
	offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
	*((unsigned int *)(data->image_addr + offset)) = color;
}

void    draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < WIN_HEIGHT / 29)
    {
        hor = 0;
        while (hor < WIN_WIDTH / 29)
        {
            my_mlx_pixel_put(mlx, WIN_WIDTH / 29*i + hor, WIN_HEIGHT / 29 *j + ver, color);
            hor++;
        }
        ver++;
    }
}

void draw_map(t_mlx *mlx, t_map *map)
{
    int i = 0;
    int j = 0;
    while(map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == '1')
                draw_pixels(i, j, map->C_color, mlx);
            else if (map->map[i][j] == '0')
                draw_pixels(i, j, map->F_color, mlx);
            else
                draw_pixels(i, j, 0x00FF0000, mlx);
            j++;
        }
        i++;
    }
}