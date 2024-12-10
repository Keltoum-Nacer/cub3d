#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include "../minilibx-linux/mlx_int.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>
// macro parsing
#define SUCCESS 1
#define FAILURE 0
#define MAP_HEIGHT 1000
#define BUFFER_SIZE 7
#define INV_TEX ": Invalid texture(s)\n"
#define NOT_XPM " Not an .xpm file\n"
#define NOT_CUB " Not an .cub file\n"
#define WR_NBR "Wrong number of arguments\n"
#define DUP "duplicates\n"
#define INV_RGB " Invalid RGB value \n"
#define MIS_COL " Missing color(s)\n"
#define ER_OPEN " Error in opening file \n"
#define EMPTY "Empty map\n"
#define SMALL "Map too small\n"
#define MAP "Invalid map!\n"
#define DOOR "Invalid door!\n"
#define PLAYER "The map should contain one player!\n"

//macro draw

# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_A 97
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define KEY_LEFT 65363
# define KEY_RIGHT 65361

typedef struct s_player
{
    float p_x;
    float p_y;
    char  p_name;

}t_player;

typedef struct s_map
{
    char *north;
    char *west;
    char *east;
    char *south;
    char *map[MAP_HEIGHT];  // Updated with the parsing changes
    int F_color;
    int C_color;
    int width;
    int height;  // Added from parsing
    int height_text;
    t_player p;
} t_map;

typedef struct s_mlx
{
    void    *mlx;
    void    *window;
    void    *image;
    char    *image_addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;

}t_mlx;

typedef struct s_bres_flag
{
	int		dx;
	int		dy;
	int		sx;
	int		err;
	int		sy;
}			t_bres_flag;

typedef struct s_point
{
    int x_ind;
    int y_ind;
}t_point;

typedef struct s_data
{
    t_mlx mlx;
    t_map map;
}
t_data;
// parsing functions

int file_cub(int fd, char *name);
char    *ft_getline(int fd);
void    ft_put_str(char *str, char *name);
int parse_direction(int fd, t_map **map);
char *extract_directory_path(int fd, int flag, t_map **map);
int validate_position(char *line, int flag);
int file_xpm(char *name);
int parse_color(int fd, t_map **map);
int extract_and_validate_int(char *line, int *pos);
long long transform_sequence(char *line);
int extract_color_value(int fd, int flag, t_map **map);
int parse_color(int fd, t_map **map);
int parse_map(int fd, int fdd, t_map *map);
char	*get_next_line(int fd);
int valid_character(t_map *map);
int    read_map(int fd, int fdd, t_map *map);
int check_0(char **new_map, t_map *map);
void    free_map(char **arr, t_map *map);
void    print_err(char *str);

// function 2D
void draw_map(t_data *data);
void    draw_pixels(int i, int j, int color, t_mlx *mlx);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);


//test array
void	bresenham(t_point p0, t_point p1, t_data *data);
void	init_flag(t_bres_flag *s, t_point p0, t_point p1);
void field_of_view(t_map map, t_point *y);
void init_mlx(t_mlx *mlx);
void init_data(t_map map, t_data *data);
int handle_key(int keycode, t_data *data);
void move_player(t_data *data);
#endif
