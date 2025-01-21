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
