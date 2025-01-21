#include "../../include_files/cub3d_bonus.h"

void	print_err(char *str)
{
	ft_putstr_fd("CUB3D >> Error :: ", 2);
	ft_putstr_fd(str, 2);
}

int	check_left_right(char c, t_map *map)
{
	if (c != '0' && c != '1' && c != map->p.p_name)
		return (0);
	return (1);
}

int	check_top_bottom(char c, t_map *map)
{
	if (c != '0' && c != '1' && c != map->p.p_name && c != 'D')
		return (0);
	return (1);
}

int	check_0(char **new_map, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (new_map[i][j] == '0' && (!check_left_right(new_map[i][j - 1],
						map) || !check_left_right(new_map[i][j + 1], map)
					|| !check_top_bottom(new_map[i + 1][j], map)
					|| !check_top_bottom(new_map[i - 1][j], map)))
				return (print_err(MAP), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

void	free_map(char **arr, t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(arr[i]);
		i++;
	}
}
