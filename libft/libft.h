
#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *c);

void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_atoi(const char *c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strstr(const char *haystack, const char *needle);
int		ft_whitespace(char c);
int		ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *str, const char *src, size_t size);
void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char *s, char c);

#endif
