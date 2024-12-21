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
void draw_pixels_mini_map(int i, int j, int color, t_mlx *mlx, float scale_x, float scale_y)
{
    int x;
    int y;

    (void)scale_x;
    (void)scale_y;
    x = 0;
    while(x < MINI_GRID)
    {
        y = 0;
        while(y < MINI_GRID)
        {
            my_mlx_pixel_put(mlx, (WIN_WIDTH - MINI_DIM) + MINI_GRID * i + x, MINI_GRID * j + y, color);
            y++;
        }
        x++;
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
    int i;
    int j;

    i = 0;
    while( i < 5)
    {
        j = 0;
        while(j < 5)
        {
            my_mlx_pixel_put(mlx, (WIN_WIDTH - MINI_DIM) + x * 15 + i, y * 15 + j, color);
            j++;
        }
        i++;
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
    // t_point player;

    // player.x_ind = data->map.p.p_x;
    // player.y_ind = data->map.p.p_y;
    (void)i;
    p1.x_ind = p0.x_ind + 25 * cos(alpha);
    p1.y_ind = 25 * sin(alpha) + p0.y_ind;
    init_flag(&s, p0, p1);
    while (1)
    {
        if ((int)p0.x_ind ==(int) p1.x_ind && (int)p0.y_ind == (int)p1.y_ind)
        {
            printf("i am here\n");
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
void    draw_mini_map(t_data *data)
{
   // float   scale;
    float   scale_x;
    float   scale_y;
    int     i;
    int     j;

    i = 0;
    scale_x = ((float)data->map.width / (WIN_WIDTH/ MINI_DIM)) * MINI_GRID;
    scale_y = ((float)data->map.height / (WIN_WIDTH / MINI_DIM)) * MINI_GRID;
   // scale = fmin(scale_x, scale_y);
    while(data->map.map[i])
    {
        j = 0;    
        while(data->map.map[i][j])
        {
            if (data->map.map[i][j] == '1')
                draw_pixels_mini_map(j, i, 0xDB7093, &data->mlx, scale_x, scale_y);
            else if (data->map.map[i][j] == ' ')
                draw_pixels_mini_map(j, i, 0xC71585, &data->mlx, scale_x,scale_y);
            else 
                draw_pixels_mini_map(j, i, 0xFFB6C1, &data->mlx, scale_x, scale_y);

            j++;
        }
        i++;
    }
    draw_mini_player(data->map.p.p_x / 64, data->map.p.p_y / 64, 0x000000, &data->mlx);
    draw_raycasting_mini_map(data);
}


// void    draw_mini_map(t_data *data)
// {
//     float   scale_x;
//     float   scale_y;
//     int     i, j;
//     int     player_x = data->map.p.p_x / 64; // Player x in grid coordinates
//     int     player_y = data->map.p.p_y / 64 ; // Player y in grid coordinates
//     int     mini_map_size = MINI_DIM; // Mini-map size
//     int     zoom_level = 3; // Zoom level (e.g., 3x3 area around the player)
//     int     start_x = player_x - zoom_level / 2;
//     int     start_y = player_y - zoom_level / 2;
//     int     end_x = player_x + zoom_level / 2;
//     int     end_y = player_y + zoom_level / 2;

//     // Ensure the coordinates are within bounds
//     if (start_x < 0) start_x = 0;
//     if (start_y < 0) start_y = 0;
//     if (end_x >= data->map.width) end_x = data->map.width - 1;
//     if (end_y >= data->map.height) end_y = data->map.height - 1;

//     scale_x = ((float)data->map.width / (WIN_WIDTH / mini_map_size)) * MINI_GRID;
//     scale_y = ((float)data->map.height / (WIN_WIDTH / mini_map_size)) * MINI_GRID;

//     // Draw the region of the mini-map around the player
//     i = start_y;
//     while (i <= end_y) 
//     {
//         j = start_x;
//         while (j <= end_x) 
//         {
//             if (data->map.map[i][j] == '1')
//                 draw_pixels_mini_map(j, i, 0xDB7093, &data->mlx, scale_x, scale_y);
//             else if (data->map.map[i][j] == ' ')
//                 draw_pixels_mini_map(j, i, 0xC71585, &data->mlx, scale_x, scale_y);
//             else
//                 draw_pixels_mini_map(j, i, 0xFFB6C1, &data->mlx, scale_x, scale_y);

//             j++;
//         }
//         i++;
//     }

//     // Draw the player at the center of the zoomed-in mini-map
//     draw_mini_player((player_x - start_x) * MINI_GRID, (player_y - start_y) * MINI_GRID, 0x000000, &data->mlx);

//     // Optionally, draw raycasting information or other data
//     draw_raycasting_mini_map(data);
// }