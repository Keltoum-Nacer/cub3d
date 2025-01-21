#include "../include_files/cub3d_bonus.h"

int	init_textures(t_data *data)
{
	char	*names[7];
	int		i;

	names[0] = data->map.south;
	names[1] = data->map.north;
	names[2] = data->map.east;
	names[3] = data->map.west;
	names[4] = ft_strdup("textures/simonkraft/door.xpm");
	names[5] = ft_strdup("textures/simonkraft/palestine15.xpm");
	names[6] = ft_strdup("textures/simonkraft/palestine17.xpm");
	i = 0;
	while (i < 7)
	{
		data->ts[i].t.image = mlx_xpm_file_to_image(data->mlx.mlx, names[i],
				&data->text.width, &data->text.height);
		if (!data->ts[i].t.image)
			return (write(2, FAILED_DOWN, 40));
		data->ts[i].t.image_addr = mlx_get_data_addr(data->ts[i].t.image,
				&data->ts[i].t.bits_per_pixel, &data->ts[i].t.line_length,
				&data->ts[i].t.endian);
		i++;
	}
	return (free(names[4]), free(names[5]), free(names[6]), 1);
}

void	draw_start(t_data *data)
{
	int		i;
	char	path[256];

	i = 0;
	while (i < 66)
	{
		snprintf(path, sizeof(path), PATH_FORMAT, i + 1);
		data->text.frames[i].image = mlx_xpm_file_to_image(data->mlx.mlx, path,
				&data->text.width, &data->text.height);
		if (!data->text.frames[i].image)
		{
			write(2, FAILED_DOWN, 40);
			return ;
		}
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.window,
			data->text.frames[i].image, 0, 0);
		if (i == 43)
			sleep(1);
		mlx_destroy_image(data->mlx.mlx, data->text.frames[i].image);
		usleep(100000);
		i++;
	}
}

void	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return ;
	data->mlx.image = mlx_new_image(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->mlx.image_addr = mlx_get_data_addr(data->mlx.image,
			&data->mlx.bits_per_pixel, &data->mlx.line_length,
			&data->mlx.endian);
	data->mlx.window = mlx_new_window(data->mlx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"FREE PALESTINE");
	if (!data->mlx.window)
		return ;
	if (data->text.hidden)
		draw_start(data);
	init_textures(data);
}

void	init_data(t_map map, t_data *data)
{
	data->text.hidden = 1;
	data->map = map;
	data->map.open_door = 0;
	data->map.p.p_y *= WALL_DIM;
	data->map.p.p_x *= WALL_DIM;
	if (map.p.p_name == 'N')
		data->map.p.angle = 3 * PI / 2;
	if (map.p.p_name == 'W')
		data->map.p.angle = PI;
	if (map.p.p_name == 'S')
		data->map.p.angle = PI / 2;
	if (map.p.p_name == 'E')
		data->map.p.angle = 0;
	data->flag = 0;
	data->flag_weast = 0;
	data->flag_east = 0;
	init_mlx(data);
}
