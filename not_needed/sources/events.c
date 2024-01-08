#include "../includes/minirt.h"

int	close_window(int keycode, t_vars *vars)
{
    //(void)keycode;
    (void)vars;
    printf("close_window keycode: %d\n", keycode);
    if (keycode == 53)
    {
        printf("successful window close keycode: %d\n", keycode);

	    mlx_destroy_window(vars->mlx, vars->win);
        exit(0);

        return 0;
    }

	return (-1);
}


//camera movements, WASD
int mlx_hook_camera_movements(int keycode, t_vars *vars)
{
    printf("mlx_hook_camera_movements keycode: %d\n", keycode);
    (void)vars;
    if (keycode == 13)
    {
        //w
        printf("camera moved up\n");
        return 0;
    }
    else if (keycode == 0)
    {
        //a
        printf("camera moved left\n");
        return 0;
    }
    else if (keycode == 1)
    {
        //s
        printf("camera moved down\n");
        return 0;
    }
    else if (keycode == 2)
    {
        //d
        printf("camera moved right\n");
        return 0;
    }

    return -1;

}


//camera rotations, up, down, left right
int mlx_hook_camera_rotation(int keycode, t_vars *vars)
{
    printf("mlx_hook_camera_rotation keycode: %d\n", keycode);

    (void)vars;
    if (keycode == 126)
    {
        //up
        printf("camera rotated up\n");
        return 0;
    }
    else if (keycode == 123)
    {
        //left
        printf("camera rotated left\n");
        return 0;
    }
    else if (keycode == 125)
    {
        //down
        printf("camera rotated down\n");
        return 0;
    }
    else if (keycode == 124)
    {
        //right
        printf("camera rotated right\n");
        return 0;
    }

    return -1;
}

//zoom, in = n, out = m
int mlx_hook_zoom(int keycode, t_vars *vars)
{
    printf("mlx_hook_zoom keycode: %d\n", keycode);

    (void)vars;
    if (keycode == 45)
    {
        //in
        printf("camera zoomed in\n");
        return 0;
    }
    else if (keycode == 46)
    {
        //left
        printf("camera zoomed out\n");
        return 0;
    }
    return -1;
}