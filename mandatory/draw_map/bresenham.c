#include "../../include_files/cub3d.h"

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

void	render_wall_projection(t_point p0, t_data *data, double alpha, int i)
{
	double	dis_to_proj;
	double	precise_dist;
	int		start;
	int		end;

	alpha = normalize_angle(alpha);
	data->map.p.ray_angle = alpha;
	precise_dist = data->map.p.wall_dist * cos(alpha - data->map.p.angle);
	dis_to_proj = (WIDTH / 2) / tan(degree_to_rad(FOV / 2));
	data->map.p.wall_height = round((dis_to_proj / precise_dist) * WALL_DIM);
	start = (HEIGHT / 2) - (int)(data->map.p.wall_height / 2);
	end = (HEIGHT / 2) + (int)(data->map.p.wall_height / 2);
	data->map.p.hit_x = p0.x_ind;
	data->map.p.hit_y = p0.y_ind;
	p0.x_ind = i;
	draw_wall(p0, start, end, data);
}

int	check_wall(t_point p0, double alpha, t_data *data, int i)
{
	t_point	player;

	player.x_ind = data->map.p.p_x;
	player.y_ind = data->map.p.p_y;
	if (data->map.map[(int)(p0.y_ind / WALL_DIM)][(int)(p0.x_ind
			/ WALL_DIM)] == '1')
	{
		data->map.is_door = 0;
		data->map.p.wall_dist = calculate_distance(p0, player);
		render_wall_projection(p0, data, alpha, i);
		return (1);
	}
	return (0);
}

void	init_bresenham(t_data *data, t_point p0, double alpha, t_bres_flag *s)
{
	double	max_ray_length;
	t_point	p1;

	max_ray_length = sqrt(pow(WIDTH * WALL_DIM, 2) + pow(HEIGHT * WALL_DIM, 2));
	p1.x_ind = p0.x_ind + max_ray_length * cos(alpha);
	p1.y_ind = max_ray_length * sin(alpha) + p0.y_ind;
	data->map.p.ray_angle = alpha;
	init_flag(s, p0, p1);
}

void	bresenham(t_point p0, double alpha, t_data *data, int i)
{
	t_bres_flag	s;
	int			e2;

	init_bresenham(data, p0, alpha, &s);
	while (1)
	{
		if (check_wall(p0, alpha, data, i))
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
