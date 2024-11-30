/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 14:32:48 by sait-amm          #+#    #+#             */
/*   Updated: 2024/11/30 14:32:49 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libft.h"

static char	*ft_cpy(const char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*d;
	int		len1;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1) + ft_strlen(s2);
	d = (char *)malloc((len1 + 1) * sizeof(char const));
	if (!d)
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	d[i + j] = '\0';
	return (d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*d;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	d = ft_cpy(s1, s2);
	return (d);
}
