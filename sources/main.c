#include "../includes/minirt.h"

//create the location of the pixel and actually put the image on the screen
void plot_pixel(void *mlx, void *mlx_win, t_data img, int x, int y,  int color)
{
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    my_mlx_pixel_put(&img, x, y, color);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int	close_window(int keycode, t_vars *vars)
{
    (void)keycode;
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}


int main(void)
{
	t_vars	*vars;
    vars = malloc(sizeof (struct s_vars));
    t_data img;

    
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(vars->mlx, 1920, 1080);
	mlx_hook(vars->win, 2, 1L<<0, close_window, &vars);
    //Bresenham_line_algorithm(50, 50, 1000, 1000, mlx, mlx_win, img);
    //draw_shaded_circle(500, 500, 100, mlx, mlx_win, img);

    mlx_loop(vars->mlx);
}
