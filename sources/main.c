#include "../includes/minirt.h"

//create the location of the pixel and actually put the image on the screen
void plot_pixel(void *mlx, void *mlx_win, t_data img, int x, int y)
{
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    my_mlx_pixel_put(&img, x, y, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main(void)
{
    void *mlx;
    void *mlx_win;
    t_data img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    Bresenham_line_algorithm(50, 50, 1000, 1000, mlx, mlx_win, img);
    //midpoint_circle_algorithm(500, 500, 100, mlx, mlx_win, img);

    mlx_loop(mlx);
}
