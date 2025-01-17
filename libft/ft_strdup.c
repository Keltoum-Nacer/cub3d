/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knacer <knacer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 22:53:34 by knacer            #+#    #+#             */
/*   Updated: 2025/01/17 22:53:35 by knacer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*d;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (s1[len])
		len++;
	d = (char *)s1;
	d = malloc((len + 1) * sizeof(char));
	if (!d)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}
