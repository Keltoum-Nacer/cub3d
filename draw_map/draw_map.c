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

void    draw_mini_player(int x, int y, int color, t_mlx *mlx)
{
    double i, angle, x1, y1;
    int r;

    r  = 5;
    i = 0;
    while(i <= r)
    {
        angle = 0;
        while(angle < 360)
        {
            x1 = i * cos(angle * PI / 180);
            y1 = i * sin(angle * PI / 180);
            my_mlx_pixel_put(mlx, (WIN_WIDTH - MINI_DIM) + x * MINI_GRID + x1, y * MINI_GRID + y1, color);
            angle += 0.1;
        }
        i += 0.1;
    }
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
    draw_mini_map(data);
}

void bresenham_mini_map(t_point p0, double alpha, t_data *data, int i)
{
    t_bres_flag s;
    int e2;
    t_point p1;
    (void)i;
    p1.x_ind = p0.x_ind + 25 * cos(alpha);
    p1.y_ind = 25 * sin(alpha) + p0.y_ind;
    init_flag(&s, p0, p1);
    while (1)
    {
        if ((int)p0.x_ind ==(int) p1.x_ind && (int)p0.y_ind == (int)p1.y_ind)
        {
            break;
        }
        my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, 0xFFAE41);
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx;
        }
        if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy;
        }
    }
}

void draw_raycasting_mini_map(t_data *data)
{
    double fov = degree_to_rad(FOV);
    double angle_step = fov / NUM_RAYS;
    double ray_angle;
    t_point x;
    int i;

    ray_angle = degree_to_rad(data->map.p.angle) - (fov / 2);
    x.x_ind = (WIN_WIDTH - MINI_DIM) + (data->map.p.p_x)/64 * 15 ;
    x.y_ind = (data->map.p.p_y/ 64 )* 15;

    i = 0;
    while (i < 450)
    {
        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        bresenham_mini_map(x, ray_angle, data, i);
        ray_angle += angle_step;
        i++;
    }
}
// void    draw_mini_map(t_data *data)
// {
//     int     i;
//     int     j;

//     i = 0;
//     while(data->map.map[i])
//     {
//         j = 0;    
//         while(data->map.map[i][j])
//         {
//             if (data->map.map[i][j] == '1')
//                 draw_pixels_mini_map(j, i, 0xDB7093, &data->mlx);
//             else if (data->map.map[i][j] == ' ')
//                 draw_pixels_mini_map(j, i, 0xC71585, &data->mlx);
//             else 
//                 draw_pixels_mini_map(j, i, 0xFFB6C1, &data->mlx);

//             j++;
//         }
//         i++;
//     }
//     draw_mini_player(data->map.p.p_x / 64, data->map.p.p_y / 64, 0x000000, &data->mlx);
//     draw_raycasting_mini_map(data);
// }
void draw_pixels_mini_map(int i, int j, int color, t_mlx *mlx)
{
    int x;
    int y;

    x = 0;
    while (x < MINI_GRID)
    {
        y = 0;
        while (y < MINI_GRID)
        {
            my_mlx_pixel_put(mlx, (WIN_WIDTH - MINI_DIM) + MINI_GRID * i + x, MINI_GRID * j + y, color);
            y++;
        }
        x++;
    }
}


void draw_mini_map(t_data *data)
{
    int i, j;
    int player_x, player_y;
    int view_radius = 5; 

    player_x = data->map.p.p_x / 64; 
    player_y = data->map.p.p_y / 64;

    i = 0;
    while (data->map.map[i]) 
    {
        j = 0;
        while (data->map.map[i][j]) 
        {
            if (abs(i - player_y) <= view_radius && abs(j - player_x) <= view_radius) 
            {
                if (data->map.map[i][j] == '1')
                    draw_pixels_mini_map(j, i, 0xDB7093, &data->mlx);
                else if (data->map.map[i][j] == ' ')
                    draw_pixels_mini_map(j, i, 0xC71585, &data->mlx);
                else 
                    draw_pixels_mini_map(j, i, 0xFFB6C1, &data->mlx);
            }
            j++;
        }
        i++;
    }
    draw_mini_player(player_x, player_y, 0x000000, &data->mlx);
    draw_raycasting_mini_map(data);
}


