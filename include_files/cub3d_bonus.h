#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "define.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

enum				e_HorVer
{
	VER,
	HOR,
};

typedef struct s_point
{
	double			x_ind;
	double			y_ind;
}					t_point;

typedef struct s_player
{
	double			p_x;
	double			p_y;
	double			door_dist;
	double			height_door;
	int				door;
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
	void			*image;
	char			*image_addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				img_width;
	int				img_height;

}					t_mlx;

typedef struct s_text
{
	t_mlx			t;
	t_mlx			frames[67];
	t_mlx			tank;
	t_mlx			end;
	int				width;
	int				height;
	char			*player;
	char			*name;
	int				hidden;
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
	t_text			ts[8];
	t_text			anim;
	t_mlx			player;
	int				sound;
	int				flag;
	int				wall;
	int				flag_weast;
	int				flag_east;
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
void				init_data(t_map map, t_data *data);

// ray-casting && texters
int					draw_map(t_data *data);
void				draw_pixels(int i, int j, int color, t_mlx *mlx);
void				bresenham(t_point p0, double alpha, t_data *data, int i);
void				init_flag(t_bres_flag *s, t_point p0, t_point p1);
int					handle_key(int keycode, t_data *data);
void				render_wall_projection(t_point p0, t_data *data,
						double alpha, int i);
void				draw_wall(t_point p0, int start, int end, t_data *data);
int					check_texture(t_data *data);
int					check_wall_door(t_point p0, double alpha, t_data *data,
						int i);
void				build_wall(t_point p0, int start, int end, t_data *data);
void				bresenham_mini_map(t_point p0, double alpha, t_data *data);
void				draw_raycasting(t_data *data);
void				mini_player(int x, int y, int color, t_mlx *mlx);
void				draw_player(t_data *data, char *name);
void				rendring_minimap(t_data *data);
// mlx

void				move_player(t_data *data);
void				hook_functions(t_data *data);
void				init_mlx(t_data *data);
void				my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
int					ft_close(t_data *cub);

// texters

int					build_texters(t_data *data, int i, int end, t_point p0);
int					check_texture(t_data *data);

// wall

// helper
double				degree_to_rad(float fov);
void				ft_free(char **tr);
int					ft_len_double(char **str);
void				free_dir(t_map *map, int flag);
void				destroy_all_bonus(t_data data);
int					animation_player(t_data *data);
double				normalize_angle(double alpha);
double				calculate_distance(t_point p0, t_point p1);
double				normalize_angle(double alpha);
void				ft_put_str(char *str, char *name);

#endif
