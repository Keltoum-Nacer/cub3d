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
        ray_angle = normalize_angle(ray_angle);
        bresenham(x, ray_angle, data, i);
        ray_angle += angle_step;
        i++;
    }
}

double calculate_distance(t_point p0, t_point p1)
{
    return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind, 2.)));
}


void draw_player(t_data *data, char *name)
{
    double x ;
    double offset_x = 0;
    double offset_y;
    int img_width, img_height;
    int bpp, size_line, endian;

    void *img_player = mlx_xpm_file_to_image(data->mlx.mlx, name, &img_width, &img_height);
    if (!img_player)
        return;
    double y = WIN_HEIGHT - 70 - img_height;

    void *addr = mlx_get_data_addr(img_player, &bpp, &size_line, &endian);
    if (data->flag % 2)
        x = 175;
    else
        x = 370;

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
    draw_raycasting(data);
    if (data->flag % 2)
        draw_player(data, "textures/anim_player/player1.xpm");
    else
        draw_player(data, "textures/simonkraft/player2_resize.xpm");
    draw_mini_map(data);
    return (0);
}
int draw_anim(t_data *data)
{
    int i = 0;
    char path[256];
    while (i < 27)
    {
        data->mlx.image_addr = mlx_get_data_addr(data->mlx.image, &data->mlx.bits_per_pixel, &data->mlx.line_length, &data->mlx.endian);
        mlx_do_sync(data->mlx.mlx);
        draw_raycasting(data);
        snprintf(path, sizeof(path), PATH_PLAYER, i + 1);
        if (i == 25 && data->wall)
            data->flag_weast = 1;
        else if (i == 25 && !data->wall)
            data->flag_east = 1;
        draw_player(data, path);
        mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
        draw_mini_map(data);
        usleep(40000);
        i++;
    }
    return (0);
}
