/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:03:05 by knacer            #+#    #+#             */
/*   Updated: 2025/01/17 22:03:35 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_files/cub3d_bonus.h"

int	validate_position(char *line, int flag)
{
	if (!flag && (line[0] != 'N' || line[1] != 'O'))
		return (FAILURE);
	if (flag == 1 && (line[0] != 'S' || line[1] != 'O'))
		return (FAILURE);
	if (flag == 2 && (line[0] != 'W' || line[1] != 'E'))
		return (FAILURE);
	if (flag == 3 && (line[0] != 'E' || line[1] != 'A'))
		return (FAILURE);
	return (SUCCESS);
}

char	*extract_directory_path(int fd, int flag, t_map **map)
{
	char	*line;
	char	*d;
	char	*line_trim;

	line = get_next_line(fd);
	if (!line)
		return (free(line), ft_put_str(EMPTY, NULL), NULL);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	(*map)->height_text++;
	line_trim = ft_strtrim(line, " \n\r\f\v\t");
	if (!validate_position(line_trim, flag))
		return (ft_put_str(INV_TEX, NULL), free(line), free(line_trim), NULL);
	d = ft_strdup(ft_strchr(line_trim, 't'));
	if (!file_xpm(d))
		return (free(d), free(line_trim), free(line), NULL);
	return (free(line), free(line_trim), d);
}

void	free_dir(t_map *map, int flag)
{
	if (flag == 1)
		free(map->north);
	else if (flag == 2)
	{
		free(map->north);
		free(map->south);
	}
	else if (flag == 3)
	{
		free(map->north);
		free(map->south);
		free(map->west);
	}
	else
	{
		free(map->north);
		free(map->south);
		free(map->west);
		free(map->east);
	}
}

int	parse_direction(int fd, t_map **map)
{
	char	*line;

	(*map)->north = extract_directory_path(fd, 0, map);
	if (!(*map)->north)
		return (FAILURE);
	(*map)->south = extract_directory_path(fd, 1, map);
	if (!(*map)->south)
		return (free_dir(*map, 1), FAILURE);
	(*map)->west = extract_directory_path(fd, 2, map);
	if (!(*map)->west)
		return (free_dir(*map, 2), FAILURE);
	(*map)->east = extract_directory_path(fd, 3, map);
	if (!(*map)->east)
		return (free_dir(*map, 3), FAILURE);
	line = get_next_line(fd);
	if (line[0] != '\n')
	{
		write(2, DUP, 12);
		free(line);
		free_dir(*map, 4);
		return (FAILURE);
	}
	return (free(line), SUCCESS);
}
