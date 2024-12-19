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

void draw_raycasting(t_data *data)
{
    double fov;
    t_point x;
    fov = degree_to_rad(FOV / 2);
    double angle_step = fov / NUM_RAYS;
    double alpha = 0;
    double current_angle = degree_to_rad(data->map.p.angle);
    x.x_ind = data->map.p.p_x;
    x.y_ind = data->map.p.p_y;
    int i = 1;
    while (alpha <= fov)
    {
        if (current_angle == 2 * PI)
            current_angle = 0;
        current_angle += (angle_step * i);
        bresenham(x, current_angle, data);
        alpha += angle_step;
        i++;
    }
    alpha = fov;
    current_angle = degree_to_rad(data->map.p.angle);
    while (alpha >= 0)
    {
        if (current_angle == 0)
            current_angle = 2 * PI;
        bresenham(x, current_angle, data);
        current_angle -= (angle_step * i);
        alpha -= angle_step;
        i++;
    }
}


double calculate_distance(t_point p0, t_point p1)
{
    return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind, 2.)));
}

void draw_wall(t_point p0, t_data *data, double alpha)
{

    double dis_to_proj;
    double  wall_height;
    double  precise_dist;
        precise_dist = data->map.p.dist * cos(alpha - degree_to_rad(data->map.p.angle));

        dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(FOV / 2));
        
        wall_height = (dis_to_proj / precise_dist) * WALL_DIM;
        //printf("==========================>> %f\n", dis_to_proj);
   
        bresenham_wall(p0, wall_height, data);
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
    
}
