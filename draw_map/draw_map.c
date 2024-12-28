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

void     draw_mini_player(int x, int y, int color, t_mlx *mlx)
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
            my_mlx_pixel_put(mlx, x * MINI_GRID + x1, y * MINI_GRID + y1, color);
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
    // draw_image(data);
    // draw_player(data->map.p.p_x, data->map.p.p_y, 0XFFFFFFFF, &data->mlx);
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
    x.x_ind = 5 * 15;
    x.y_ind = 5 * 15;

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
            my_mlx_pixel_put(mlx, i + x, j + y, color);
            y++;
        }
        x++;
    }
}

// void draw_circle(double x, double y,int color, t_mlx *mlx)
// {
//     double  angle;
//     double  i;
//     double  j;
//     int r;

//     angle = 0;
//     r = 90;
//     while(angle < 360)
//     {
//         i = r * cos(angle * PI / 180);
//         j = r * sin(angle * PI / 180);
//         my_mlx_pixel_put(mlx, (WIN_WIDTH - MINI_DIM) + x * MINI_GRID + i, y * MINI_GRID + j, color);
//         angle += 0.1;
//     }
//}

void draw_circle(int x, int y, int radius, int color, t_mlx *mlx)
{
    int dx, dy;
    int p;

    // Start drawing the circle
    dx = 0;
    dy = radius;
    p = 1 - radius;  // Initial decision parameter

    // Using the Midpoint Circle Drawing Algorithm to draw a circle
    while (dx <= dy)
    {
        // Draw the 8 symmetric points of the circle
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x + dx, WIN_HEIGHT - 1000 + y + dy, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x - dx, WIN_HEIGHT - 1000 + y + dy, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x + dx, WIN_HEIGHT - 1000 + y - dy, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x - dx, WIN_HEIGHT - 1000 + y - dy, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x + dy, WIN_HEIGHT - 1000 + y + dx, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x - dy, WIN_HEIGHT - 1000 + y + dx, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x + dy, WIN_HEIGHT - 1000 + y - dx, color);
        my_mlx_pixel_put(mlx, WIN_WIDTH - 1850 + x - dy, WIN_HEIGHT - 1000 + y - dx, color);

        // Update decision parameter
        if (p < 0)
            p += 2 * dx + 3;
        else
        {
            p += 2 * (dx - dy) + 5;
            dy--;
        }
        dx++;
    }
}


void draw_mini_map(t_data *data)
{
    int i, j;
    double center_x, center_y;
    double dx, dy, dist_squared;
    int radius = VIEW_RADIUS * MINI_GRID * 15;

    center_x = data->map.p.p_x / 64;
    center_y = data->map.p.p_y / 64;

    i = 0;
    while (data->map.map[i])
    {
        j = 0;
        while (data->map.map[i][j])
        {
            dx = j - center_x;
            dy = i - center_y;  
            dist_squared = dx * dx + dy * dy;
            if (dist_squared <= VIEW_RADIUS * VIEW_RADIUS)
            {
                int tile_x = (dx + VIEW_RADIUS) * 15;  
                int tile_y = (dy + VIEW_RADIUS) * 15; 

                if (tile_x * tile_x + tile_y * tile_y <= radius * radius)
                {
                    if (data->map.map[i][j] == '1')
                        draw_pixels_mini_map(tile_x, tile_y, 0xDB7093, &data->mlx);
                    else if (data->map.map[i][j] == ' ')
                        draw_pixels_mini_map(tile_x, tile_y, 0xC71585, &data->mlx);
                    else
                        draw_pixels_mini_map(tile_x, tile_y, 0xFFB6C1, &data->mlx);
                }
            }
            j++;
        }
        i++;
    }
    draw_mini_player(5, 5, 0x000000, &data->mlx);
    draw_raycasting_mini_map(data);
}

// void draw_mini_map(t_data *data)
// {
//     double center_x;
//     double center_y;
//     double angle;
//     int rayon;
//     double x1;
//     double y1;
//     int i;
//     center_x = data->map.p.p_x / 64;
//     center_y = data->map.p.p_y / 64;
//     angle = 0;
//     rayon = 100;
//     i = 0;
//     while(i <= rayon)
//     {
//         while(angle < 360)
//         {
//             x1 = i * cos(angle * PI / 180);
//             y1 = i * sin(angle * PI / 180);
//             if (data->map.map[(int)(y1 + center_y) / 15][(int)(x1 + center_x) / 15] == '1')
//                 my_mlx_pixel_put(&data->mlx, x1 + 150, y1 + 150, 0xDB7093);
//             else if (data->map.map[(int)(y1 + center_y) / 15][(int)(x1 + center_x) / 15] == ' ')
//                 draw_pixels_mini_map(x1 + 150, y1 + 150, 0xC71585, &data->mlx);
//             else
//                 draw_pixels_mini_map(x1 + 150, y1 + 150, 0xFFB6C1, &data->mlx);
//             angle += 0.1;
//         }
//         i += 0.1;
//     }
// }


// void draw_mini_map(t_data *data)
// {
//     int i, j;
//     double center_x, center_y;
//     double dx, dy, dist_squared;
//     int radius = VIEW_RADIUS * MINI_GRID * 15; 
//     center_x = data->map.p.p_x / 64;
//     center_y = data->map.p.p_y / 64;

//     // Iterate over the map
//     i = 0;
//     while (data->map.map[i])
//     {
//         j = 0;
//         while (data->map.map[i][j])
//         {
//             dx = j - center_x;
//             dy = i - center_y;
//             dist_squared = dx * dx + dy * dy;

//             if (dist_squared <= VIEW_RADIUS * VIEW_RADIUS)
//             {
//                 int x = (dx + VIEW_RADIUS) * 15;
//                 int y = (dy + VIEW_RADIUS) * 15;

//                 if (x * x + y * y <= radius * radius)
//                 {
//                     if (data->map.map[i][j] == '1')
//                         draw_pixels_mini_map(x, y, 0xDB7093, &data->mlx);
//                     else if (data->map.map[i][j] == ' ')
//                         draw_pixels_mini_map(x, y, 0xC71585, &data->mlx);
//                     else 
//                         draw_pixels_mini_map(x, y, 0xFFB6C1, &data->mlx);
//                 }
//             }
//             j++;
//         }
//         i++;
//     }

//     draw_mini_player(5, 5, 0x000000, &data->mlx);
//     draw_raycasting_mini_map(data);
// }


// int	is_corner(char c)
// {
// 	if (!c || c == ' ' || c == '\n')
// 		return (0);
// 	return (1);
// }

// void	draw_pixels_mini_map(t_data *x, double i, double j, t_point start)
// {
// 	double	b;
// 	double	a;

// 	a = start.y_ind / 64 + i / MINI_GRID;
// 	b = start.x_ind / 64 + j / MINI_GRID;
// 	if (a >= 0 && a < x->map.height && b >= 0 && b < x->map.width && is_corner(x->map.map[(int)a][(int)b]) && ((int)(start.x_ind * MINI_GRID / 64 + j) % MINI_GRID == 0 || (int)(start.y_ind * MINI_GRID / 64 + i) % MINI_GRID == 0))
// 		my_mlx_pixel_put(&x->mlx, (WIN_WIDTH - MINI_DIM) + j, i, 0x000000);
// 	if (a >= 0 && a < x->map.height && b >= 0 && b < x->map.width && x->map.map[(int)a][(int)b] == '1')
// 		my_mlx_pixel_put(&x->mlx, (WIN_WIDTH - MINI_DIM) + j, i, 0xDB7093);
// 	else if (a >= 0 && a < x->map.height && b >= 0 && b < x->map.width
// 		&& x->map.map[(int)a][(int)b] == '0')
// 		my_mlx_pixel_put(&x->mlx, (WIN_WIDTH - MINI_DIM) + j, i, 0xd0d3d4);
// 	else if (a >= 0 && a < x->map.height && b >= 0 && b < x->map.width
// 		&& (x->map.map[(int)a][(int)b] == 'D'))
// 		my_mlx_pixel_put(&x->mlx, (WIN_WIDTH - MINI_DIM) + j, i, 0x0);
// 	else if (a >= 0 && a < x->map.height && b >= 0 && b < x->map.width
// 		&& (x->map.map[(int)a][(int)b] == ' '))
// 		my_mlx_pixel_put(&x->mlx, (WIN_WIDTH - MINI_DIM) + j, i, 0xFFFFFF);
// }

// void	color_one_square(int start_x, int start_y, void *x)
// {
// 	int		i;
// 	int		j;
// 	double	s_x;
// 	double	s_y;
// 	int		color;

// 	i = 0;
// 	j = 0;
// 	s_x = start_x - MINI_GRID / 2;
// 	s_y = start_y - MINI_GRID / 2;
// 	color = 0xf1c40f;
// 	while (i <= MINI_GRID)
// 	{
// 		j = 0;
// 		while (j <= MINI_GRID)
// 		{
// 			if (i <= (MINI_GRID - 3) && j <= (MINI_GRID - 3) && i >= 3
// 				&& j >= 3)
// 				my_mlx_pixel_put(x, (WIN_WIDTH - MINI_DIM) + (s_x + i), (s_y + j), color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_line_angle(t_data *data, int x0, int y0)
// {
// 	int	i;
// 	int	x;
// 	int	y;

// 	i = 0;
// 	while (i < 20)
// 	{
// 		x = x0 + i * cos(data->map.p.angle);
// 		y = y0 + i * sin(data->map.p.angle);
// 		if (x >= 0 && y >= 0)
// 			my_mlx_pixel_put(&data->mlx, x, y, 0xff0000);
// 		i++;
// 	}
// }

// void	draw_mini_map(t_data *x)
// {
// 	double			width;
// 	double			height;
// 	t_point	start;
// 	double			i;
// 	double			j;

// 	width = 40;
// 	height = 40;
// 	start.x_ind = (x->map.p.p_x - 64 * width / 2) / 64 * MINI_GRID;
// 	start.y_ind = (x->map.p.p_y - 64 * height / 2) / 64 * MINI_GRID;
// 	i = MINI_GRID;
// 	while (i < height * MINI_GRID)
// 	{
// 		j = MINI_GRID;
// 		while (j < width * MINI_GRID)
// 		{
// 			draw_pixels_mini_map(x, i, j, start);
// 			j++;
// 		}
// 		i++;
// 	}
// 	color_one_square((width * MINI_GRID) / 2, (height * MINI_GRID) / 2, x);
//     //draw_mini_player(x->map.p.p_x /64, x->map.p.p_y / 64, 0x000000, &x->mlx);
// 	//draw_line_angle(x, (width * MINI_GRID) / 2, (height * MINI_GRID)/ 2);
// }



