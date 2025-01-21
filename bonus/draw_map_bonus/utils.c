#include "../../include_files/cub3d_bonus.h"

double	normalize_angle(double alpha)
{
	if (alpha < 0)
		alpha += 2 * PI;
	if (alpha > 2 * PI)
		alpha -= 2 * PI;
	return (alpha);
}

double	degree_to_rad(float fov)
{
	double	rad;

	rad = fov * PI / DEGREE_180;
	return (rad);
}

double	calculate_distance(t_point p0, t_point p1)
{
	return (sqrt(powf(p0.x_ind - p1.x_ind, 2.) + powf(p0.y_ind - p1.y_ind,
				2.)));
}

void	ft_put_str(char *str, char *name)
{
	write(2, CUB_ERR, 14);
	if (name)
		write(2, name, ft_strlen(name) - 1);
	write(2, str, ft_strlen(str) - 1);
}
