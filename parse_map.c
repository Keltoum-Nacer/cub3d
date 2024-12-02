#include "cub3d.h"

void    print_err(char *str)
{
    ft_putendl_fd(str, 2);
    exit(1);
}

char    *ft_getline(int fd)
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

void    ft_parse_line(int fd, t_map *map)
{
    char    *line;
    int     i;

    while(line = ft_getline(fd))
	{
		
		free (line);
	}
    
}    

void    ft_parse_map(char *map_file, t_map *map)
{
    int fd;
	

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
    {
        perror(map_file);
        exit(1);
    }
    ft_parse_line(fd, map);
}