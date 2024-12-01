/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:45:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/12/01 15:28:51 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "../libft/libft.h"
#define  SUCCESS 1
#define  FAILURE 0
#define INV_TEX ": Invalid texture(s)\n"
#define WR_NBR "Wrong number of arguments\n"
typedef struct s_map
{
    char *north;
    char *west;
    char *east;
    char *south;
    char **map;
    int F_color;
    int C_color;
} t_map;

// parcing functions

int file_cub(int fd, char *name);
char    *ft_getline(int fd);
void    ft_put_str(char *str, char *name);
int parce_direction(int fd, t_map **map);
char *add_dir(int fd, int flag);
int validate_position(char *line, int flag);
#endif