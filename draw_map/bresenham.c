#include "../include_file/cub3d.h"

void init_flag(t_bres_flag *s, t_point p0, t_point p1)
{
    s->dx = abs((int)p1.x_ind - (int)p0.x_ind);
    s->dy = abs((int)p1.y_ind - (int)p0.y_ind);
    if (p0.x_ind < p1.x_ind)
        s->sx = 1;
    else if (p0.x_ind > p1.x_ind)
        s->sx = -1;
    if (p0.y_ind < p1.y_ind)
        s->sy = 1;
    else if (p0.y_ind > p1.y_ind)
        s->sy = -1;
    s->err = s->dx - s->dy;
}

unsigned int darkness(unsigned int color, double distance, int max_distance)
{
    double dark_factor;
    int r;
    int g;
    int b;

    dark_factor = 1 - (distance / max_distance);
    if (dark_factor < 0)
        dark_factor = 0;
    if (dark_factor > 1)
        dark_factor = 1;
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
    r = r * dark_factor;
    g = g * dark_factor;
    b = b * dark_factor;
    return ((r << 16) | (g << 8) | b);
}

int set_wall_color(t_data *data)
{
    double normalized_angle;

    // Normalize the ray angle to [0, 2*PI]
    normalized_angle = fmod(data->map.p.ray.angle, 2 * PI);
    if (normalized_angle < 0)
        normalized_angle += 2 * PI;

    if (!data->map.p.ray.ver_hor) // Horizontal hit
    {
        if (normalized_angle > 0 && normalized_angle < PI)
            return (0xD239FF); // South-facing wall
        else
            return (0xFF25CD); // North-facing wall
    }
    else // Vertical hit
    {
        if (normalized_angle > 3 * (PI / 2) || normalized_angle < PI / 2)
            return (0x66D7FF); // East-facing wall
        else
            return (0x000000); // West-facing wall
    }
    return (0);
}

int check_texture(t_data *data)
{
    if (!data->map.p.ray.ver_hor)
        data->map.p.ray.texture_x = fmod(data->map.p.ray.wall_intersection.x_ind, WALL_DIM) / WALL_DIM * data->text.width;
    else
        data->map.p.ray.texture_x = fmod(data->map.p.ray.wall_intersection.y_ind, WALL_DIM) / WALL_DIM * data->text.width;
    if (!data->map.p.ray.ver_hor)
    {
        if (data->map.p.ray.angle > 0 && data->map.p.ray.angle < PI)
            return (data->textures[0].name = data->map.south, 0);
        else
            return (data->textures[1].name = data->map.north, 1);
    }
    else
    {
        if (data->map.p.ray.angle > (3 * PI) / 2 || data->map.p.ray.angle < PI / 2)
            return (data->textures[2].name = data->map.east, 2);
        else
            return (data->textures[3].name = data->map.west, 3);
    }
    return (0);
}
void bresenham_wall(t_point p0, int start, int end, t_data *data)
{
    int i = 0;
    int j;
    while (i < start)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.C_color);
        i++;
    }
    p0.y_ind = start;
    j = check_texture(data);
    double texture_step = (double)data->text.height /data->map.p.wall_height;
    double texture_pos = 0.0;
    if (end > WIN_HEIGHT)
        end = WIN_HEIGHT;
    double tex_y ;
     while (i < end)
    {
        tex_y = texture_pos;
        if (data->map.p.ray.texture_x >= 0 && data->map.p.ray.texture_x < data->text.width)
        {
            int color = *(int *)(data->textures[j].text_mlx.image_addr +
                                 ((int)tex_y * data->textures[j].text_mlx.line_length) +
                                 ((int)data->map.p.ray.texture_x * (data->textures[j].text_mlx.bits_per_pixel / 8)));
            // color = darkness(color, data->map.p.dist, WIN_HEIGHT);
            // int color = set_wall_color(data);
            my_mlx_pixel_put(&data->mlx, p0.x_ind, i, color);
        }
        texture_pos += texture_step;
        // if (texture_pos < 0)
        //     texture_pos = 0;
        // if (texture_pos >= data->text.height)
        //     texture_pos = data->text.height - 1;
        i++;
    }

    while (i < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.F_color);
        i++;
    }
}

void draw_wall(t_point p0, t_data *data, double alpha, int i)
{
    double dis_to_proj;
    double precise_dist;

    if (alpha < 0)
        alpha += 2 * PI;
    if (alpha >= 2 * PI)
        alpha -= 2 * PI;
    data->map.p.ray.angle = alpha;
    precise_dist = data->map.p.ray.wall_dist * cos(alpha - degree_to_rad(data->map.p.angle));
    dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(FOV / 2));
    data->map.p.wall_height = round((dis_to_proj / precise_dist) * WALL_DIM);
    int start = (WIN_HEIGHT / 2) - (int)(data->map.p.wall_height / 2);
    int end = (WIN_HEIGHT / 2) + (int)(data->map.p.wall_height / 2);
    p0.x_ind = i;
    data->map.p.ray.wall_intersection.x_ind = p0.x_ind;
    data->map.p.ray.wall_intersection.y_ind = p0.y_ind;
    bresenham_wall(p0, start, end, data);
}

void bresenham(t_point p0, double alpha, t_data *data, int i)
{
    t_bres_flag s;
    int e2;
    t_point p1;
    t_point player;

    player.x_ind = data->map.p.p_x;
    player.y_ind = data->map.p.p_y;
    double max_ray_length = sqrt(pow(data->map.width * WALL_DIM, 2) + pow(MAP_HEIGHT * WALL_DIM, 2));
    p1.x_ind = p0.x_ind + max_ray_length * cos(alpha);
    p1.y_ind = max_ray_length * sin(alpha) + p0.y_ind;
    data->map.p.ray.angle = alpha;
    init_flag(&s, p0, p1);
    while (1)
    {
        if (data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind / WALL_DIM)] == '1')
        {
            data->map.p.ray.wall_dist = calculate_distance(p0, player);
            draw_wall(p0, data, alpha, i);
            break;
        }
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx; // Step horizontally
            data->map.p.ray.ver_hor = 1;
        }
        else if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy; // Step vertically
            data->map.p.ray.ver_hor = 0;
        }
    }
}
