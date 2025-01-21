#include "libft.h"

int	ft_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\n'
		|| c == '\v')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *c)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_whitespace(c[i]) == 1)
		i++;
	if (c[i] == '+' || c[i] == '-')
	{
		if (c[i] == '-')
			sign = (-1) * sign;
		i++;
	}
	while (c[i] >= '0' && c[i] <= '9')
	{
		result = result * 10 + c[i] - '0';
		i++;
	}
	return (result * sign);
}
