#include "../../include_files/cub3d.h"

void	init_textures(t_data *data)
{
	char	*names[4];
	int		i;

	names[0] = data->map.south;
	names[1] = data->map.north;
	names[2] = data->map.east;
	names[3] = data->map.west;
	i = 0;
	while (i < 4)
	{
		data->texts[i].t.img = mlx_xpm_file_to_image(data->mlx.mlx, names[i],
				&data->text.width, &data->text.height);
		if (!data->texts[i].t.img)
		{
			write(2, FAILED_DOWN, 40);
			return ;
		}
		data->texts[i].t.addr = mlx_get_data_addr(data->texts[i].t.img,
				&data->texts[i].t.bpp, &data->texts[i].t.line_len,
				&data->texts[i].t.end);
		i++;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return ;
	data->mlx.img = mlx_new_image(data->mlx.mlx, WIDTH, HEIGHT);
	data->mlx.addr = mlx_get_data_addr(data->mlx.img, &data->mlx.bpp,
			&data->mlx.line_len, &data->mlx.end);
	data->mlx.window = mlx_new_window(data->mlx.mlx, WIDTH, HEIGHT,
			"Our Cub3D");
	if (!data->mlx.window)
		return ;
	init_textures(data);
}

void	init_data(t_map map, t_data *data)
{
	data->map = map;
	data->map.p.p_y *= WALL_DIM;
	data->map.p.p_x *= WALL_DIM;
	if (map.p.p_name == 'N')
		data->map.p.angle = (3 * PI) / 2;
	if (map.p.p_name == 'W')
		data->map.p.angle = PI;
	if (map.p.p_name == 'S')
		data->map.p.angle = PI / 2;
	if (map.p.p_name == 'E')
		data->map.p.angle = 0;
	init_mlx(data);
}

double	normalize_angle(double alpha)
{
	if (alpha < 0)
		alpha += 2 * PI;
	if (alpha > 2 * PI)
		alpha -= 2 * PI;
	return (alpha);
}
