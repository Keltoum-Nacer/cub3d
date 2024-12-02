/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:01:09 by sait-amm          #+#    #+#             */
/*   Updated: 2024/12/02 15:07:39 by sait-amm         ###   ########.fr       */
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
int parce_map(char *name, t_map *map)
{
    int fd;
    fd = open(name, O_RDONLY);
    if (!file_cub(fd, name))
        return(FAILURE);
    if (!parce_direction(fd, &map) || !parce_color(fd, &map))
        return (FAILURE);
    close(fd);
    return(SUCCESS);
}
int main(int ac, char **av)
{
    t_map map;
    
    if (ac != 2)
    {
        write(2, WR_NBR , 26);
        return (EXIT_FAILURE);
    }
    if (!parce_map(av[1], &map))
        return(FAILURE);
    printf("***%s\n", map.north);
    printf("***%s\n", map.south);
    printf("***%s\n", map.west);
    printf("***%s\n", map.east);
    printf(">>>%d\n", map.C_color);
    printf(">>>%d\n", map.F_color);
    free(map.north);
    free(map.south);
    free(map.west);
    free(map.east);
}
