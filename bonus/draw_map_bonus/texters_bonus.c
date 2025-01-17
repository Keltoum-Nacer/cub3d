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

int set_wall_color(t_data *data)
{
    double normalized_angle;

    // Normalize the ray angle to [0, 2*PI]
    normalized_angle = fmod(data->map.p.ray_angle, 2 * PI);
    if (normalized_angle < 0)
        normalized_angle += 2 * PI;

    if (!data->map.p.flag) // Horizontal hit
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
    if (!data->map.p.flag)
        data->map.p.offset_x = fmod(data->map.p.hit_x, WALL_DIM) / WALL_DIM * data->text.width;
    else
        data->map.p.offset_x = fmod(data->map.p.hit_y, WALL_DIM) / WALL_DIM * data->text.width;
    if (data->map.is_door)
        return(4);
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
            return ( 3);
    }
    return 0;
}
