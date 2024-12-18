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
// void draw_raycasting(t_data *data)
// {
//     double fov;
//     t_point x;
//     fov = degree_to_rad(30);
//     double angle_step = fov / NUM_RAYS;
//     double alpha = 0;
//     double current_angle = degree_to_rad(data->map.p.angle);
//     int i = 0;
//     x.x_ind = data->map.p.p_x;
//     x.y_ind = data->map.p.p_y;

//     while (alpha <= fov)
//     {
//         if (current_angle == 2 * PI)
//             current_angle = 0;
//         bresenham(x, current_angle, data, &i);
//         current_angle += angle_step;
//         alpha += angle_step;
//     }
//     alpha = fov;
//     current_angle = degree_to_rad(data->map.p.angle);
//     while (alpha >= 0)
//     {
//         if (current_angle == 0)
//             current_angle = 2 * PI;
//         bresenham(x, current_angle, data, &i);
//         current_angle -= angle_step;
//         alpha -= angle_step;
//     }
// }

void draw_raycasting(t_data *data)
{
    double fov = degree_to_rad(60);
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
        bresenham(x, ray_angle, data, &i);
        ray_angle += angle_step;
        i++;
    }
}

double calculate_distance(t_point p0, t_point p1)
{
    return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind, 2.)));
}

void draw_wall(t_data *data)
{
    // double dis_to_proj;
    double wall_height;
    double precise_dist;
    t_point p0;
    t_point p1;
    int x = 0;
    while (x < WIN_WIDTH)
    {
        // dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(data->map.p.rays[x].angle));
        precise_dist = data->map.p.rays[x].distance * cos(data->map.p.rays[x].angle);
        p0.x_ind = x;
        p1.x_ind = x;
        if (precise_dist == 0)
        {
            x++;
            p0.x_ind = x;
            p1.x_ind = x;
            continue;
        }
        wall_height = CST / precise_dist;
        // printf("*****************%f\n", wall_height);
        p0.y_ind = WIN_HEIGHT / 2 - wall_height / 2;
        p1.y_ind = WIN_HEIGHT / 2 + wall_height / 2;
        // printf("-------== %f--------== %f\n", data->map.p.rays[1].angle,data->map.p.rays[1].distance);
        // printf("-------== %f--------== %f\n", data->map.p.rays[3].angle,data->map.p.rays[3].distance);
        // printf("****%d\n", CST);
        // printf("-------== %f--------== %f\n", p0.x_ind, p1.x_ind);
        bresenham_wall(p0, p1, data);
        x++;
    }
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
			my_mlx_pixel_put(&data->mlx, x, y, 0x000000);
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
    draw_wall(data);
}
