#include "../../include_files/cub3d.h"

int	extract_and_validate_int(char *line)
{
	int		i;
	int		ret;
	char	*nmbr;
	char	**spl;

	i = 0;
	spl = ft_split(line, ' ');
	if (ft_len_double(spl) != 1)
		return (ft_free(spl), ft_put_str(INV_RGB, NULL), -1);
	ft_free(spl);
	while (ft_whitespace(line[0]))
		line++;
	while (ft_isdigit(line[i]))
		i++;
	nmbr = ft_substr(line, 0, i);
	if (!nmbr[0])
		return (free(nmbr), ft_put_str(INV_RGB, NULL), -1);
	ret = ft_atoi(nmbr);
	if (ret >= 0 && ret <= 255)
		return (free(nmbr), ret);
	return (free(nmbr), ft_put_str(INV_RGB, NULL), -1);
}

long long	transform_sequence(char *line)
{
	int		c_red;
	int		c_green;
	int		c_blue;
	char	**pl;

	line++;
	pl = ft_split(line, ',');
	if (ft_len_double(pl) != 3)
		return (ft_put_str(MIS_COL, NULL), ft_free(pl), -1);
	c_red = extract_and_validate_int(pl[0]);
	if (c_red == -1)
		return (ft_free(pl), -1);
	c_green = extract_and_validate_int(pl[1]);
	if (c_green == -1)
		return (ft_free(pl), -1);
	c_blue = extract_and_validate_int(pl[2]);
	if (c_blue == -1)
		return (ft_free(pl), -1);
	return (ft_free(pl), (c_red << 16) | (c_green << 8) | c_blue);
}

int	affecte_color(char *line)
{
	int	color;

	color = transform_sequence(line);
	if (color == -1)
		return (free(line), -1);
	return (free(line), color);
}

int	extract_color_value(int fd, int flag, t_map **map)
{
	char	*line;
	char	*line_trim;

	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	(*map)->height_text++;
	line_trim = ft_strtrim(line, " \n\r\f\v\t");
	if (!flag && line_trim[0] == 'F')
		return (free(line), affecte_color(line_trim));
	else if (flag && line_trim[0] == 'C')
		return (free(line), affecte_color(line_trim));
	ft_put_str(MIS_COL, NULL);
	return (free(line), free(line_trim), -1);
}

int	parse_color(int fd, t_map **map)
{
	(*map)->f_color = extract_color_value(fd, 0, map);
	if ((*map)->f_color == -1)
		return (FAILURE);
	(*map)->c_color = extract_color_value(fd, 1, map);
	if ((*map)->c_color == -1)
		return (FAILURE);
	return (SUCCESS);
}
