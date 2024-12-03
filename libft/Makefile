NAME = libft.a
SRCF = ft_atoi.c \
        ft_strdup.c \
        ft_substr.c \
        ft_strjoin.c \
		ft_memcpy.c \
		ft_strlen.c \
		ft_putendl_fd.c \
		ft_putstr_fd.c \
		ft_strcmp.c \
		ft_strstr.c \
		ft_strchr.c \
		ft_isdigit.c
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
