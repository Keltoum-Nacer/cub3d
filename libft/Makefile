# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sait-amm <sait-amm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/30 14:33:09 by sait-amm          #+#    #+#              #
#    Updated: 2024/11/30 14:35:25 by sait-amm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a
SRCF = ft_atoi.c \
        ft_strdup.c \
        ft_substr.c \
        ft_strjoin.c \
		ft_memcpy.c \
		ft_strlen.c
CC = cc

CFLAGS = -Wall -Werror -Wextra

AR = ar rc

OBJF = $(SRCF:.c=.o)


all : $(NAME)

$(OBJF) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRCF)

$(NAME): $(OBJF) 
	$(AR) $(NAME) $(OBJF)


clean :
	rm -f $(OBJF)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all re clean
