/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:01:09 by sait-amm          #+#    #+#             */
/*   Updated: 2024/11/30 14:35:46 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include_file/cub3d.h"

int main(int ac, char **av)
{
    int fd;
    // t_map *map;
    
    if (ac != 2)
    {
        write(2, "Wrong number of arguments\n", 26);
        return (0);
    }
    fd = open(av[1], O_RDONLY);
    // if (check_file(fd, av[1]))
    //     return(1);
    printf("::::%d\n", fd);
    close(fd);
    
}