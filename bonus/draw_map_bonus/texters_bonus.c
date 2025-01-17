#include "../include_files/cub3d_bonus.h"

unsigned int darkness(unsigned int color, double distance, int max_distance)
{
    double	factor;
	int		r;
	int		g;
	int		b;

	factor = 2.5 - (distance / max_distance);
	if (factor < 0.1)
		factor = 0.1;
	if (factor > 1)
		factor = 1;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = r * factor;
	g = g * factor;
	b = b * factor;
	return ((r << 16) | (g << 8) | b);
}


int check_texture(t_data *data)
{
    if (!data->map.p.flag)
        data->map.p.offset_x = fmod(data->map.p.hit_x, WALL_DIM) / WALL_DIM * data->text.width;
    else
        data->map.p.offset_x =   fmod(data->map.p.hit_y, WALL_DIM) / WALL_DIM * data->text.width;
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
        {
            if(data->flag_east)
                return(2);
            return (6);
        }
        else
        {
            if (data->flag_weast)
                return (3);
            return (5);
        }
    }
    return 0;
}
