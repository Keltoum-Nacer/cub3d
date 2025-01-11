#include "../../include_files/cub3d.h"

int	file_cub(int fd, char *name)
{
	int	flag;

	flag = 0;
	if (fd < 0)
	{
		ft_put_str(ER_OPEN, name);
		return (FAILURE);
	}
	if (name[ft_strlen(name) - 1] != 'b' || name[ft_strlen(name) - 2] != 'u'
		|| name[ft_strlen(name) - 3] != 'c' || name[ft_strlen(name) - 4] != '.')
		flag++;
	if (!ft_strcmp(name, ".cub") || flag)
	{
		ft_put_str(NOT_CUB, name);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	ft_len_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_free(char **tr)
{
	int	i;

	i = 0;
	if (!tr || !(tr[0]))
		return ;
	while (tr[i])
	{
		free(tr[i]);
		i++;
	}
	free(tr);
}

int	file_xpm(char *name)
{
	int		fd;
	char	**spl;

	spl = ft_split(name, ' ');
	if (!spl || !spl[0] || ft_len_double(spl) != 1)
		return (ft_put_str(TEX_NMBR, NULL), ft_free(spl), FAILURE);
	ft_free(spl);
	if (!ft_strcmp(name, ".xpm"))
		return (ft_put_str(NOT_XPM, name), FAILURE);
	if (name[ft_strlen(name) - 1] != 'm' || name[ft_strlen(name) - 2] != 'p'
		|| name[ft_strlen(name) - 3] != 'x' || name[ft_strlen(name) - 4] != '.')
		return (ft_put_str(NOT_XPM, name), FAILURE);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror(name);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
