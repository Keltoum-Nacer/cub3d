#include "../include_file/cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= WIN_HEIGHT || y < 0 || y >= WIN_WIDTH)
        return;
    offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
    *((unsigned int *)(data->image_addr + offset)) = color;
}

void draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < 30)
    {
        hor = 0;
        while (hor < 30)
        {
            my_mlx_pixel_put(mlx, 30 * i + hor, 30 * j + ver, color);
            hor++;
        }
        ver++;
    }
}
void draw_player(int x, int y, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < 10)
    {
        hor = 0;
        while (hor < 10)
        {
            my_mlx_pixel_put(mlx, x + hor, y + ver, color);
            hor++;
        }
        ver++;
    }
}
void draw_raycasting(t_data *data)
{
    t_point x;
    int i;
    t_point y;
    t_point z;

    x.x_ind = data->map.p.p_x;
    x.y_ind = data->map.p.p_y;
    field_of_view(data->map, &y);
    i = 0;

    int tmp = y.y_ind;
    while (i < 17)
    {
        y.y_ind = tmp + i;
        while (data->map.map[y.y_ind / 30][y.x_ind / 30] != '1')
            y.x_ind++;
        bresenham(x, y, data);
        z.x_ind = y.x_ind;
        z.y_ind = tmp - i;
        while (data->map.map[z.y_ind / 30][z.x_ind / 30] != '1')
            z.x_ind++;
        bresenham(x, z, data);
        i++;
    }
}
void draw_map(t_data *data)
{
    int i = 0;
    int j = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == '1')
                draw_pixels(j, i, data->map.C_color, &data->mlx);
            else if (data->map.map[i][j] != '\n')
                draw_pixels(j, i, data->map.F_color, &data->mlx);
            j++;
        }
        i++;
    }
    draw_player(data->map.p.p_x, data->map.p.p_y, 0XFFFFFFFF, &data->mlx);
    draw_raycasting(data);
}
