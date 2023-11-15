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

int init_mlx_keyboard_hook(int keycode, t_vars *vars)
{
    printf("start init_mlx_keyboard_hook, keycode: %d\n", keycode);
    if (keycode == 53 && close_window(keycode, vars) == -1)
    {
        printf("failed to close window\n");
        return -1;
    }
    if ((keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2) && mlx_hook_camera_movements(keycode, vars) == -1){
        printf("failed to move camera\n");
        return -1;
    }
    if ((keycode >= 123 && keycode <= 126) && mlx_hook_camera_rotation(keycode, vars) == -1){
        printf("failed to rotate camera\n");
        return -1;
    }
    if ((keycode == 45 || keycode == 46) && mlx_hook_zoom(keycode, vars) == -1){
        printf("failed to zoom camera\n");
        return -1;
    }
    printf("end init_mlx_keyboard_hook\n");

    return 0;
}

int init_mlx_mouse_hook(int keycode, t_vars * vars)
{
    (void)vars;
    printf("start mouse_hook, keycode: %d\n", keycode);
    if (keycode == 1)
    {
        printf("left click\n");
    }
    else if (keycode == 2)
    {
        printf("right click\n");
    }
    else if (keycode == 3)
    {
        printf("Middle click\n");
    }
    else if (keycode == 4)
    {
        printf("Scroll up\n");
    }
    else if (keycode == 5)
    {
        printf("Scroll down\n");
    }

    return -1;
}

int main(void)
{
	t_vars	*vars;
    vars = malloc(sizeof (struct s_vars));
    t_data img;

    
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, 500, 500, "Hello world!");
    img.img = mlx_new_image(vars->mlx, 500, 500);

    //hooking things
    mlx_hook(vars->win, 3, 1L<<0, init_mlx_keyboard_hook, &vars);
    mlx_mouse_hook(vars->win, init_mlx_mouse_hook, &vars);



    //Bresenham_line_algorithm(50, 50, 1000, 1000, mlx, mlx_win, img);
    //draw_shaded_circle(500, 500, 100, mlx, mlx_win, img);

    mlx_loop(vars->mlx);
}
