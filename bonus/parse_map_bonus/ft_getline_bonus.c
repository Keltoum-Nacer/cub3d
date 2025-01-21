#include "../../include_files/cub3d_bonus.h"

char	*ft_getline(int fd)
{
	char	*buff;
	char	*tmp;
	char	*d;
	ssize_t	size;

	buff = NULL;
	tmp = malloc(2);
	if (!tmp)
		return (NULL);
	while (1)
	{
		size = read(fd, tmp, 1);
		if (size < 0)
			return (NULL);
		tmp[1] = '\0';
		d = buff;
		buff = ft_strjoin(d, tmp);
		if (tmp[0] == '\n' || !tmp)
			return (free(tmp), free(d), buff);
		free(d);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char	buffer[7000000];
	char	c;
	int		i;
	int		n_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	n_byte = read(fd, &c, 1);
	i = 0;
	while (n_byte > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
		n_byte = read(fd, &c, 1);
	}
	if (n_byte <= 0 && i == 0)
		return (NULL);
	buffer[i] = '\0';
	return (ft_strdup(buffer));
}
