/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:49:39 by knacer            #+#    #+#             */
/*   Updated: 2025/01/17 22:49:40 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	char	*ptr;
	size_t	i;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	i = 0;
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ptr = p;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
