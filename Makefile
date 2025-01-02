
SRC =  main.c \
		parse_map/check_file.c \
		parse_map/check_directions.c \
		parse_map/ft_getline.c \
		parse_map/check_color.c \
		parse_map/check_map.c \
		parse_map/check_map_utils.c \
		parse_map/read_map.c \
		draw_map/draw_map.c \
		draw_map/bresenham.c \
		draw_map/move_player.c \
		draw_map/events.c \
		initial/init.c 
		
		
LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
NAME = Cub3D
INCLUDES = -I . -I include -I $(LIBFT_DIR) 

C = cc

CFLAGS =  -Wall -Werror -Wextra -I$(MLX_DIR) -I/usr/include/X11 #-g3 -fsanitize=address 
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd -lm


all: $(NAME)

$(NAME): $(SRC) $(LIBFT_LIB) $(MLX_LIB)
	$(CC) $(CFLAGS) $(SRC) $(LIBFT_LIB) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all clean fclean re
