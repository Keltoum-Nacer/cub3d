#include "../include_files/cub3d_bonus.h"

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


int check_texture(t_data *data)
{
    if (!data->map.p.flag)
        data->map.p.offset_x = data->text.width -  fmod(data->map.p.hit_x, WALL_DIM) / WALL_DIM * data->text.width;
    else
        data->map.p.offset_x = data->text.width -  fmod(data->map.p.hit_y, WALL_DIM) / WALL_DIM * data->text.width;
    if (data->map.is_door)
        return (4);
    if (!data->map.p.flag)
    {
        if (data->map.p.ray_angle > 0 && data->map.p.ray_angle < PI)
            return (0);
        else
            return (1);
    }
    else
    {
        if (data->map.p.ray_angle > (3 * PI) / 2 || data->map.p.ray_angle < PI / 2)
            return (2);
        else
        {
            if (data->flag_palestine)
                return (3);
            return (5);
        }
    }
    return 0;
}
