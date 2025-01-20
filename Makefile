
SRC =  mandatory/main.c \
		mandatory/parse_map/check_file.c \
		mandatory/parse_map/check_directions.c \
		mandatory/parse_map/ft_getline.c \
		mandatory/parse_map/check_color.c \
		mandatory/parse_map/check_map.c \
		mandatory/parse_map/check_map_utils.c \
		mandatory/parse_map/read_map.c \
		mandatory/draw_map/draw_map.c \
		mandatory/draw_map/bresenham.c \
		mandatory/draw_map/move_player.c \
		mandatory/draw_map/events.c \
		mandatory/draw_map/init.c \
		mandatory/draw_map/texters.c
		
SRCB = bonus/main_bonus.c \
		bonus/parse_map_bonus/check_color_bonus.c \
		bonus/parse_map_bonus/check_directions_bonus.c \
		bonus/parse_map_bonus/check_file_bonus.c \
		bonus/parse_map_bonus/check_map_bonus.c \
		bonus/parse_map_bonus/check_map_utils_bonus.c \
		bonus/parse_map_bonus/ft_getline_bonus.c \
		bonus/parse_map_bonus/read_map_bonus.c \
		bonus/draw_map_bonus/bresenham_bonus.c \
		bonus/draw_map_bonus/draw_map_bonus.c \
		bonus/draw_map_bonus/events_bonus.c \
		bonus/draw_map_bonus/init_bonus.c \
		bonus/draw_map_bonus/mini_map_bonus.c \
		bonus/draw_map_bonus/move_player_bonus.c \
		bonus/draw_map_bonus/texters_bonus.c \
		bonus/draw_map_bonus/player.c  \
		bonus/draw_map_bonus/utils.c \
		bonus/draw_map_bonus/rendring_wall.c

LIBFT_DIR=libft
LIBFT_LIB=$(LIBFT_DIR)/libft.a
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
NAME = Cub3D
NAMEB = Cub3D_Bonus
INCLUDES = -I . -I include -I $(LIBFT_DIR) 

C = cc

CFLAGS =  -Wall -Werror -Wextra -I$(MLX_DIR) -I/usr/include/X11 -g3 -fsanitize=address 
MLXFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd -lm


all: $(NAME)

$(NAME): $(SRC) $(LIBFT_LIB) $(MLX_LIB) 
	$(CC) $(CFLAGS) $(SRC) $(LIBFT_LIB) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

bonus: $(NAMEB)
$(NAMEB): $(SRCB) $(LIBFT_LIB) $(MLX_LIB) $(OBJF)
	$(CC) $(CFLAGS) $(SRCB) $(LIBFT_LIB) $(MLX_LIB) $(MLXFLAGS) -o $(NAMEB)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(NAMEB)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
