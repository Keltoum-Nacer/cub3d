#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "define.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define HEIGHT 700
# define WIDTH 900
# define RAYS WIDTH

typedef struct s_point
{
	double			x_ind;
	double			y_ind;
}					t_point;

typedef struct s_ray
{
	double			hit_x;
	double			hit_y;
	double			offset_x;
	double			offset_y;
	double			angle;
	int				ver_hor;
	double			wall_dist;
}					t_ray;

enum				e_HorVer
{
	VER,
	HOR,
};

typedef struct s_player
{
	double			p_x;
	double			p_y;
	char			p_name;
	double			angle;
	double			wall_height;
	double			hit_x;
	double			hit_y;
	double			offset_x;
	double			offset_y;
	double			ray_angle;
	enum e_HorVer	flag;
	double			wall_dist;
}					t_player;

typedef struct s_map
{
	char			*north;
	char			*west;
	char			*east;
	char			*south;
	char			**map;
	char			**new_map;
	int				f_color;
	int				c_color;
	int				is_door;
	int				open_door;
	int				width;
	int				height;
	int				height_text;
	t_player		p;
}					t_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*window;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				end;
}					t_mlx;

typedef struct s_text
{
	t_mlx			t;
	int				width;
	int				height;
	char			*name;
	int				x;
	int				y;
}					t_text;

typedef struct s_bres_flag
{
	int				dx;
	int				dy;
	int				sx;
	int				err;
	int				sy;
}					t_bres_flag;

typedef struct s_data
{
	t_mlx			mlx;
	t_map			map;
	t_text			text;
	t_text			texts[5];
	double			new_x;
	double			new_y;
}					t_data;
// parsing functions

int					file_cub(int fd, char *name);
char				*ft_getline(int fd);
void				ft_put_str(char *str, char *name);
int					parse_direction(int fd, t_map **map);
char				*extract_directory_path(int fd, int flag, t_map **map);
int					validate_position(char *line, int flag);
int					file_xpm(char *name);
int					extract_and_validate_int(char *line);
int					parse_color(int fd, t_map **map);
long long			transform_sequence(char *line);
int					extract_color_value(int fd, int flag, t_map **map);
int					parse_color(int fd, t_map **map);
int					parse_map(int fd, int fdd, t_map *map);
char				*get_next_line(int fd);
int					valid_character(t_map *map);
int					read_map(int fd, int fdd, t_map *map);
int					check_0(char **new_map, t_map *map);
void				free_map(char **arr, t_map *map);
void				print_err(char *str);

// ray-casting && texters
int					draw_map(t_data *data);
void				draw_pixels(int i, int j, int color, t_mlx *mlx);
void				bresenham(t_point p0, double alpha, t_data *data, int i);
void				init_flag(t_bres_flag *s, t_point p0, t_point p1);
void				init_data(t_map map, t_data *data);
int					handle_key(int keycode, t_data *data);
double				calculate_distance(t_point p0, t_point p1);
void				render_wall_projection(t_point p0, t_data *data,
						double alpha, int i);
void				draw_wall(t_point p0, int start, int end, t_data *data);
int					check_texture(t_data *data);
void				draw_raycasting(t_data *data);

// mlx

void				move_player(t_data *data);
void				hook_functions(t_data *data);
void				init_mlx(t_data *data);
void				my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int					ft_close(t_data *cub);

// helper
double				degree_to_rad(float fov);
unsigned int		darkness(unsigned int color, double distance,
						int max_distance);
int					ft_len_double(char **str);
void				ft_free(char **tr);
void				free_dir(t_map *map, int flag);
void				destroy_all(t_data data);
double				normalize_angle(double alpha);
#endif
