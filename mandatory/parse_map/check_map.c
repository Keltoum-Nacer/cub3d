#include "../../include_files/cub3d.h"

int	surrounded_by_1(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (ft_whitespace(map->map[i][j]))
			j++;
		if ((i > 0 && i < map->height - 1) && (map->map[i][j] != '1'
			|| map->map[i][ft_strlen(map->map[i]) - 1] != '1'))
			return (print_err(MAP), FAILURE);
		while (map->map[i][j])
		{
			if ((i == 0 || i == map->height - 1) && (map->map[i][j] != '1'
				&& !ft_whitespace(map->map[i][j])))
				return (print_err(MAP), FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

char	**allocate_map(t_map *map)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!new_map)
		return (NULL);
	while (i < map->height)
	{
		new_map[i] = ft_calloc(map->width, sizeof(char));
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

int	valid_map(t_map *map)
{
	int	i;
	int	j;

	map->new_map = allocate_map(map);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			map->new_map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	if (!check_0(map->new_map, map))
		return (ft_free(map->new_map), FAILURE);
	ft_free(map->new_map);
	return (SUCCESS);
}

int	parse_map(int fd, int fdd, t_map *map)
{
	if (!read_map(fd, fdd, map))
		return (FAILURE);
	if (!map->map || !map->map[0])
		return (print_err(EMPTY), FAILURE);
	if (map->height <= 2)
		return (FAILURE);
	else if (!valid_character(map))
		return (FAILURE);
	else if (!surrounded_by_1(map))
		return (FAILURE);
	else if (!valid_map(map))
		return (FAILURE);
	return (SUCCESS);
}
