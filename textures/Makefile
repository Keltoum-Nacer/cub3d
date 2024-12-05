
SRC =  main.c \
		parce_map/check_file.c \
		parce_map/check_directions.c \
		parce_map/ft_getline.c \
		parce_map/check_color.c
		
		
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
NAME = Cub3D
INCLUDES = -I . -I include -I $(LIBFT_DIR)  

C = cc

CFLAGS =  -Wall -Werror -Wextra -g3 -fsanitize=address 

all: $(NAME)

$(NAME): $(SRC) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT_LIB) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re
