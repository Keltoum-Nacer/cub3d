/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:45:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/11/30 15:28:33 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include"libft.h"
#include"mlx.h"

typedef struct s_map
{
    char *north;
    char *west;
    char *eart;
    char *south;
    char **map;
    int F_color;
    int C_color;
} t_map;
#endif