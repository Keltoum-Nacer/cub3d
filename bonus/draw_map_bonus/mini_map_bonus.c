
#include "../include_files/cub3d_bonus.h"



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
        my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, 0x008000);
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx;
        }
        else if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy;
        }
    }
}

void draw_raycasting_mini_map(t_data *data)
{
    double fov = degree_to_rad(FOV);
    double angle_step = fov /NUM_RAYS ;
    double ray_angle;
    t_point x;
    int i;

    ray_angle = data->map.p.angle - (fov / 2);
    x.x_ind = 5.1 * 15;
    x.y_ind = 5.1 * 15;

    i = 0;
    while (i < NUM_RAYS)
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

void draw_mini_map(t_data *data)
{
    int i, j;
    double center_x, center_y;
    double dx, dy, dist_squared;

    center_x = (data->map.p.p_x / WALL_DIM);
    center_y = (data->map.p.p_y / WALL_DIM);

    i = 0;
    while (i < data->map.height)
    {
        j = 0;
        while (j < data->map.width)
        {
            dx = j - center_x;
            dy = i - center_y;  
            dist_squared = dx * dx + dy * dy;
            if (dist_squared <= VIEW_RADIUS * VIEW_RADIUS)
            {
                int tile_x = (dx + VIEW_RADIUS) * 15;  
                int tile_y = (dy + VIEW_RADIUS) * 15; 
                    if (data->map.map[i][j] == '1')
                        draw_pixels_mini_map(tile_x, tile_y, 0xB22222, &data->mlx);
                    else if (data->map.map[i][j] == ' ')
                        draw_pixels_mini_map(tile_x, tile_y, 0x000000, &data->mlx);
                    else if(data->map.map[i][j] == 'D' && !data->map.open_door)
                        draw_pixels_mini_map(tile_x, tile_y, 0x008000, &data->mlx);
                    else
                        draw_pixels_mini_map(tile_x, tile_y, 0xFFFAFA, &data->mlx);
            }
            j++;
        }
        i++;
    }
     draw_mini_player(5.5, 5.5, 0x000000, &data->mlx);
     draw_raycasting_mini_map(data);
}



