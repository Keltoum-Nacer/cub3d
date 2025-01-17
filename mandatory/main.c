/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:56:58 by knacer            #+#    #+#             */
/*   Updated: 2025/01/17 22:00:23 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_files/cub3d.h"

void	ft_put_str(char *str, char *name)
{
	write(2, "cub3D: Error: ", 14);
	if (name)
		write(2, name, ft_strlen(name) - 1);
	write(2, str, ft_strlen(str) - 1);
}

int	parse_gmap(char *name, t_map *map)
{
	int	fd;
	int	fdd;

	fd = open(name, O_RDONLY);
	fdd = open(name, O_RDONLY);
	map->height_text = 0;
	if (!file_cub(fd, name))
		return (FAILURE);
	if (!parse_direction(fd, &map) || !parse_color(fd, &map))
		return (FAILURE);
	if (!parse_map(fd, fdd, map))
	{
		return (FAILURE);
	}
	close(fd);
	close(fdd);
	return (SUCCESS);
}

void	destroy_all(t_data data)
{
	int	i;

	i = 0;
	if (data.mlx.img)
		mlx_destroy_image(data.mlx.mlx, data.mlx.img);
	if (data.mlx.window)
		mlx_destroy_window(data.mlx.mlx, data.mlx.window);
	while (i < 4)
	{
		if (data.texts[i].t.img)
			mlx_destroy_image(data.mlx.mlx, data.texts[i].t.img);
		i++;
	}
	mlx_destroy_display(data.mlx.mlx);
	if (data.mlx.mlx)
		free(data.mlx.mlx);
	ft_free(data.map.map);
	free(data.map.north);
	free(data.map.south);
	free(data.map.east);
	free(data.map.west);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_data	data;

	if (ac != 2)
	{
		write(2, WR_NBR, 26);
		return (EXIT_FAILURE);
	}
	if (!parse_gmap(av[1], &map))
		return (FAILURE);
	init_data(map, &data);
	draw_map(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.window, data.mlx.img, 0, 0);
	hook_functions(&data);
	mlx_loop(data.mlx.mlx);
	destroy_all(data);
	return (0);
}
