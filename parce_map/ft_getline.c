#include "../include_file/cub3d.h"

char	*get_next_line(int fd)
{
	char buffer[7000000];
	char c;
	int i;
	int n_byte;

	if (fd < 0 || BUFFER_SIZE <= 0)
	       return(NULL);
	n_byte = read(fd, &c, 1);
	i = 0;
	while(n_byte > 0)
	{
		buffer[i++] = c;
		if(c == '\n')
			break;
		n_byte = read(fd, &c, 1);
	}
	if (n_byte <= 0 && i == 0)
		return(NULL);
	buffer[i] = '\0';
	return(ft_strdup(buffer));
}
