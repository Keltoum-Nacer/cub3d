/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:45:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/12/02 14:59:18 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "../libft/libft.h"
#define  SUCCESS 1
#define  FAILURE 0
#define INV_TEX ": Invalid texture(s)\n"
#define NOT_XPM " Not an .xpm file\n"
#define NOT_CUB " Not an .cub file\n"
#define WR_NBR "Wrong number of arguments\n"
#define DUP "duplicates\n"
#define INV_RGB " Invalid RGB value \n"
#define MIS_COL " Missing color(s)\n"
#define ER_OPEN " Error in opening file \n"
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
char *extract_directory_path(int fd, int flag);
int validate_position(char *line, int flag);
int file_xpm(char *name);
int parce_color(int fd, t_map **map);
int extract_and_validate_int(char *line, int *pos);
int transform_sequence(char *line);
int extract_color_value(int fd, int flag);
int parce_color(int fd, t_map **map);
#endif