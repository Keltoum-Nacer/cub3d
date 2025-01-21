#include "libft.h"

static int	ft_len(const char *s, char c)
{
	int	i;
	int	len;
	int	flag;

	i = 0;
	len = 0;
	flag = 0;
	while (s[i])
	{
		if (s[i] == c)
			flag = 0;
		else if (flag == 0)
		{
			flag = 1;
			len++;
		}
		i++;
	}
	return (len);
}

static int	sub_len(const char *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_cpy(const char *s, char c)
{
	char	*d;
	int		i;
	int		w;

	i = 0;
	w = sub_len(s, c);
	d = (char *)malloc(sizeof(char) * (w + 1));
	if (!d)
		return (NULL);
	while (s[i] && i < w)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static void	ft_free(char **str, int i)
{
	while (i > 0)
		free(str[--i]);
	free(str);
}

char	**ft_split(char *s, char c)
{
	char	**str;
	int		i;
	int		cw;

	if (!s)
		return (NULL);
	cw = ft_len(s, c);
	str = (char **)malloc((cw + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (i < cw)
	{
		while (*s == c)
			s++;
		str[i] = ft_cpy(s, c);
		if (!str[i++])
		{
			ft_free(str, i);
			return (NULL);
		}
		s = s + ft_strlen(str[i - 1]);
	}
	str[i] = NULL;
	return (str);
}
