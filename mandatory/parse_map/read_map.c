#include "../../include_files/cub3d.h"

int	height_map(int fdd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fdd);
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			count++;
		free(line);
		line = get_next_line(fdd);
	}
	return (count);
}

int	check_player(t_map *map, char player, int i, int j)
{
	if (player == 'N' || player == 'S' || player == 'E' || player == 'W')
	{
		map->p.p_x = (float)j;
		map->p.p_y = (float)i;
		map->p.p_name = player;
		return (1);
	}
	return (0);
}

int	valid_character(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (!ft_whitespace(map->map[i][j]) && map->map[i][j] != '0'
				&& map->map[i][j] != '1' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'W')
				return (print_err(MAP), FAILURE);
			count += check_player(map, map->map[i][j], i, j);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (print_err(PLAYER), FAILURE);
	return (SUCCESS);
}

int	full_map(t_map *map, char **str, int fd)
{
	char	*line;
	int		j;
	int		i;

	i = 1;
	line = get_next_line(fd);
	while (line)
	{
		while (line && !ft_strcmp(line, "\n") && i == 1)
			(free(line), line = get_next_line(fd));
		if (line && ft_strcmp(line, "\n"))
		{
			*str = ft_strjoin(*str, line);
			j = ft_strlen(line);
			if (j > map->width)
				map->width = j;
			i++;
		}
		else if (line && i <= map->height - map->height_text)
			return (free(line), print_err(MAP), FAILURE);
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

int	read_map(int fd, int fdd, t_map *map)
{
	char	*str;

	map->width = 0;
	map->height = height_map(fdd);
	str = NULL;
	map->height = full_map(map, &str, fd);
	if (!map->height)
		return (free(str), FAILURE);
	map->height -= 1;
	map->map = ft_split(str, '\n');
	free(str);
	return (SUCCESS);
}
