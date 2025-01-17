/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:54:17 by knacer            #+#    #+#             */
/*   Updated: 2025/01/17 22:54:42 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *str, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (src[j] != '\0')
		j++;
	if (size == 0)
		return (j);
	while (src[i] != '\0' && i < (size - 1))
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (j);
}
