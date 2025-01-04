#include "../include_file/cub3d.h"


unsigned int	darkness(unsigned int color, double distance, int max_distance)
{
	double	dark_factor;
	int		r;
	int		g;
	int		b;

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



// int check_texture(t_data *data)
// {
//      if (!data->map.p.ray.ver_hor)
//         data->map.p.ray.offset_x= fmod(data->map.p.ray.wall_intersection.x_ind, WALL_DIM) / WALL_DIM * data->text.width;
//     else
//         data->map.p.ray.offset_x= fmod(data->map.p.ray.wall_intersection.y_ind, WALL_DIM) / WALL_DIM * data->text.width;
//     if (!data->map.p.ray.ver_hor)
//     {
//         if (data->map.p.ray.angle > 0 && data->map.p.ray.angle < PI)
//             return(data->textures[0].name = data->map.south, 0);
//         else
//             return(data->textures[1].name = data->map.north, 1);
//     }
//     else
//     {
//          if (data->map.p.ray.angle > (3 * PI ) / 2 || data->map.p.ray.angle < PI / 2)
//             return(data->textures[2].name = data->map.east, 2);
//         else
//             return(data->textures[3].name = data->map.west, 3);
//     }
//     return(0);
    
// }


int check_texture(t_data *data)
{
    if (!data->map.p.ray.ver_hor)
        data->map.p.ray.offset_x = (int)data->map.p.ray.wall_intersection.x_ind % (int)WALL_DIM ;
    else
        data->map.p.ray.offset_x = (int)data->map.p.ray.wall_intersection.y_ind % (int) WALL_DIM ;

    // if (data->map.p.ray.offset_x < 0)
    //     data->map.p.ray.offset_x = 0;
    // if (data->map.p.ray.offset_x >= data->text.width)
    //     data->map.p.ray.offset_x = data->text.width - 1;
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

    return 0;
}
