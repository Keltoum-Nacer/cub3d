#include "../include_file/cub3d.h"

void my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    int offset;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    offset = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
    *((unsigned int *)(data->image_addr + offset)) = color;
}

void draw_pixels(int i, int j, int color, t_mlx *mlx)
{
    int ver = 0;
    int hor = 0;
    while (ver < WALL_DIM)
    {
        hor = 0;
        while (hor < WALL_DIM)
        {
            my_mlx_pixel_put(mlx, WALL_DIM * i + hor, WALL_DIM * j + ver, color);
            hor++;
        }
        ver++;
    }
}
void draw_pixels_mini_map(int i, int j, int color, t_mlx *mlx)
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

void draw_mini_player(int x, int y, int color, t_mlx *mlx)
{
    int ver;
    int hor;

    ver = 0;
    hor = 0;
    while(ver < 10)
    {
        hor = 0;
        while (hor < 10)
        {
            my_mlx_pixel_put(mlx, 10 * x + hor, 10 * y + ver, color);
            hor++;
        }
        ver++;
    }
}

double degree_to_rad(float fov)
{
    double rad;

    rad = fov * PI / 180.0;
    return (rad);
}

void draw_player(int x, int y, int color, t_mlx *mlx)
{
    my_mlx_pixel_put(mlx, x, y, color);
}
void draw_raycasting(t_data *data)
{
    double fov = degree_to_rad(FOV);
    double angle_step = fov / NUM_RAYS;
    double ray_angle;
    t_point x;
    int i;

    ray_angle = degree_to_rad(data->map.p.angle) - (fov / 2);
    x.x_ind = data->map.p.p_x;
    x.y_ind = data->map.p.p_y;

    i = 0;
    while (i < NUM_RAYS)
    {
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        bresenham(x, ray_angle, data, i);
        ray_angle += angle_step;
        i++;
    }
}

double calculate_distance(t_point p0, t_point p1)
{
    return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind, 2.)));
}

void	draw_image(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			my_mlx_pixel_put(&data->mlx, x, y, 0xFFFFFF);
			y++;
		}
		x++;
	}
}
void draw_map(t_data *data)
{
    draw_image(data);
    draw_player(data->map.p.p_x, data->map.p.p_y, 0XFFFFFFFF, &data->mlx);
    draw_raycasting(data);
}

void    draw_mini_map(t_data *data)
{
   
    int     i;
    int     j;

    data->mini_mlx = data->mlx;
    data->mini_mlx.mlx = mlx_init();
    if (!data->mini_mlx.mlx)
        return;
    data->mini_mlx.image = mlx_new_image(data->mini_mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!data->mini_mlx.image)
        return;
    data->mini_mlx.image_addr = mlx_get_data_addr(data->mini_mlx.image, &data->mini_mlx.bits_per_pixel, &data->mini_mlx.line_length, &data->mini_mlx.endian);
    data->mini_mlx.window = mlx_new_window(data->mini_mlx.mlx, 450, 390, "mini map");
    if (!data->mini_mlx.window)
        return;
    i = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == '1')
                draw_pixels_mini_map(j, i, data->map.C_color, &data->mini_mlx);
            else
                draw_pixels_mini_map(j, i, data->map.F_color, &data->mini_mlx);
            j++;
        }
        i++;
    }
	 draw_mini_player(data->map.p.p_y / 64, data->map.p.p_x / 64, 0xFFFFFF, &data->mini_mlx);
    mlx_put_image_to_window(data->mini_mlx.mlx, data->mini_mlx.window, data->mini_mlx.image, 0, 0);
   
}
