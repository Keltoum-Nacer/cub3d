#include "../include_files/cub3d_bonus.h"

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

double degree_to_rad(float fov)
{
    double rad;

    rad = fov * PI / 180.0;
    return (rad);
}
void draw_raycasting(t_data *data)
{
    double fov = degree_to_rad(FOV);
    double angle_step = fov / NUM_RAYS;
    double ray_angle;
    t_point x;
    int i;

    ray_angle = data->map.p.angle - (fov / 2);
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

void draw_tank(t_data *data)
{
    int i;
    int j;

    i = 0;
    data->text.tank.image = mlx_xpm_file_to_image(data->mlx.mlx, "textures/simonkraft/tank.xpm", &data->text.width, &data->text.height);
    if (!data->text.tank.image)
    {
        printf("the image cannot be loaded successfully\n");
        return;
    }
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            if (data->map.map[i][j] == 'T')
            {
                mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->text.tank.image, 0, 0);
            }
            j++;
        }
        i++;
    }
}
void draw_player(t_data *data)
{
    double x = 175;
    double offset_x = 0;
    double offset_y;
    int img_width, img_height;
    int bpp, size_line, endian;

    void *img_player = mlx_xpm_file_to_image(data->mlx.mlx, "textures/gun-removebg-preview.xpm", &img_width, &img_height);
    if (!img_player)
        return;
    double y = WIN_HEIGHT - 70 - img_height;

    void *addr = mlx_get_data_addr(img_player, &bpp, &size_line, &endian);

    while (offset_x < img_width)
    {
        offset_y = 0;
        while (offset_y < img_height)
        {
            int color = *(int *)(addr + (int)(offset_y * size_line + offset_x * (bpp / 8)));
            if (color != TRANSPARENT_COLOR)
                my_mlx_pixel_put(&data->mlx, x + offset_x, y + offset_y, color);
            offset_y++;
        }
        offset_x++;
    }
}

int draw_map(t_data *data)
{
    // mlx_clear_window(data->mlx.mlx, data->mlx.window);
    draw_raycasting(data);
    draw_player(data);
    // draw_tank(data);
    draw_mini_map(data);
    return (0);
}
