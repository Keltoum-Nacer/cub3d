/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:01:09 by sait-amm          #+#    #+#             */
/*   Updated: 2024/12/02 13:35:32 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_file/cub3d.h"

void    ft_put_str(char *str, char *name)
{
    write(2, "cub3D: Error: ", 14);
    if (name)
        write(2, name, ft_strlen(name) -1);
    write(2, str, ft_strlen(str) -1);
}
int main(int ac, char **av)
{
    int fd;
    t_map *map;
    
    if (ac != 2)
    {
        write(2, WR_NBR , 26);
        return (EXIT_FAILURE);
    }
    fd = open(av[1], O_RDONLY);
    if (!file_cub(fd, av[1]))
        return(1);
    map = malloc(sizeof(t_map));
    if (!map)
        return(EXIT_FAILURE);
    if (!parce_direction(fd, &map) || !parce_color(fd, &map))
        return (free(map), EXIT_FAILURE);
    free(map);
    close(fd);
}
