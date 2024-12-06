
#include "include_file/cub3d.h"

void ft_put_str(char *str, char *name)
{
    write(2, "cub3D: Error: ", 14);
    if (name)
        write(2, name, ft_strlen(name) - 1);
    write(2, str, ft_strlen(str) - 1);
}

int parse_Gmap(char *name, t_map *map)
{
    int fd;
    fd = open(name, O_RDONLY);
    if (!file_cub(fd, name))
        return (FAILURE);
    if (!parse_direction(fd, &map) || !parse_color(fd, &map))
        return (FAILURE);
    if (!parse_map(fd, &map))
        return (FAILURE);
    close(fd);
    return (SUCCESS);
}


void    init_mlx(t_mlx *mlx)
{
    mlx->mlx = mlx_init();
    if (!mlx->mlx)
        return ;
    mlx->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx->image_addr =  mlx_get_data_addr(mlx->image, &mlx->bits_per_pixel, &mlx->line_length,&mlx->endian);
    mlx->window = mlx_new_window(mlx->mlx, WIN_HEIGHT, WIN_WIDTH, "Our Cub3D");
    if (mlx->window == NULL)
        return ;
}
int main(int ac, char **av)
{
    t_map map;
    t_mlx mlx;

    if (ac != 2)
    {
        write(2, WR_NBR, 26);
        return (EXIT_FAILURE);
    }
    if (!parse_Gmap(av[1], &map))
        return (FAILURE);
    init_mlx(&mlx);
    draw_map(&mlx, &map);
    mlx_put_image_to_window(mlx.mlx, mlx.window, mlx.image, 0, 0);
    mlx_loop(mlx.mlx);
}
