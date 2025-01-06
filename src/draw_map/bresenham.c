#include "../../include_file/cub3d.h"

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
void draw_wall(t_point p0, int start, int end, t_data *data)
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
    double texture_step = (double)data->text.height / data->map.p.wall_height;
    double texture_pos = 0.0;                                  
    while (i < end)
    {
        double tex_y = texture_pos;
        if (data->map.p.offset_x >= 0 && data->map.p.offset_x < data->text.width)
        {
            int color = *(int *)(data->textures[j].text_mlx.image_addr +
                                ((int)tex_y * data->textures[j].text_mlx.line_length) +
                                ((int)data->map.p.offset_x* (data->textures[j].text_mlx.bits_per_pixel / 8)));
                my_mlx_pixel_put(&data->mlx, p0.x_ind, i, color);

       }
        texture_pos += texture_step;
        i++;
    }

    while (i < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&data->mlx, p0.x_ind, i, data->map.F_color);
        i++;
    }
}

void render_wall_projection(t_point p0, t_data *data, double alpha, int i)
{
    double dis_to_proj;
    double precise_dist;

    if (alpha < 0)
        alpha += 2 * PI;
    if (alpha >= 2 * PI)
        alpha -= 2 * PI;
    data->map.p.ray_angle = alpha;
    precise_dist = data->map.p.wall_dist * cos(alpha - data->map.p.angle);
    dis_to_proj = (WIN_WIDTH / 2) / tan(degree_to_rad(FOV / 2));
    data->map.p.wall_height = round((dis_to_proj / precise_dist) * WALL_DIM);
    int start = (WIN_HEIGHT / 2) - (int)(data->map.p.wall_height / 2);
    int end = (WIN_HEIGHT / 2) + (int)(data->map.p.wall_height / 2);
    p0.x_ind = i;
    data->map.p.hit_x = p0.x_ind;
    data->map.p.hit_y = p0.y_ind;
    draw_wall(p0, start, end, data);
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
    data->map.p.ray_angle = alpha;
    init_flag(&s, p0, p1);
    while (1)
    {
        if (data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind / WALL_DIM)] == '1')
        {
            data->map.is_door = 0;
            data->map.p.wall_dist = calculate_distance(p0, player);
            render_wall_projection(p0, data, alpha, i);
            break;
        }
        e2 = s.err * 2;
        if (e2 > -s.dy)
        {
            s.err -= s.dy;
            p0.x_ind += s.sx;
            data->map.p.flag = HOR;
        }
        else if (e2 < s.dx)
        {
            s.err += s.dx;
            p0.y_ind += s.sy;                                                   
            data->map.p.flag = VER;
        }
    }
}
