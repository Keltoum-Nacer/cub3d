#include "../include_files/cub3d_bonus.h"

void	init_flag(t_bres_flag *s, t_point p0, t_point p1)
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

void	setup_bresenham(t_data *data, t_point p0, double alpha, t_bres_flag *s)
{
	double	max_ray_length;
	t_point	p1;

	max_ray_length = sqrt(pow(WIN_WIDTH * WALL_DIM, 2) + pow(WIN_HEIGHT
				* WALL_DIM, 2));
	p1.x_ind = p0.x_ind + max_ray_length * cos(alpha);
	p1.y_ind = max_ray_length * sin(alpha) + p0.y_ind;
	data->map.p.ray_angle = alpha;
	init_flag(s, p0, p1);
}

void	bresenham(t_point p0, double alpha, t_data *data, int i)
{
	t_bres_flag	s;
	int			e2;

	setup_bresenham(data, p0, alpha, &s);
	while (1)
	{
		if (check_wall_door(p0, alpha, data, i))
			break ;
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

void	bresenham_mini_map(t_point p0, double alpha, t_data *data)
{
	t_bres_flag	s;
	int			e2;
	t_point		p1;

	p1.x_ind = p0.x_ind + 9 * cos(alpha);
	p1.y_ind = 9 * sin(alpha) + p0.y_ind;
	init_flag(&s, p0, p1);
	while (1)
	{
		if ((int)p0.x_ind == (int)p1.x_ind && (int)p0.y_ind == (int)p1.y_ind)
			break ;
		my_mlx_pixel_put(&data->mlx, p0.x_ind, p0.y_ind, COLOR_MINI);
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
