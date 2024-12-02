/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:11:04 by sait-amm          #+#    #+#             */
/*   Updated: 2024/12/02 10:54:37 by sait-amm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>

int ft_atoi(const char *c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strdup(const char *s1);
void *ft_memcpy(void *dest, const void *src, size_t n);
size_t ft_strlen(const char *str);
int ft_strcmp(const char *s1, const char *s2);
char *ft_strstr(const char *haystack, const char *needle);
int ft_whitespace(char c);
int ft_isdigit(int c);
char *ft_strchr(const char *s, int c);
#endif
