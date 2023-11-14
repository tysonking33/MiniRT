#include "../includes/minirt.h"

// empty circle using midpoint circle algorithm
void midpoint_circle_algorithm_empty(int x1, int y1, int radius, void *mlx, void *mlx_win, t_data img)
{
    int x = radius;
    int y = 0;
    int t1 = 1 - radius;  // Initial decision parameter

    while (x >= y)
    {
        // Plot points with center at (x1, y1)
        plot_pixel(mlx, mlx_win, img, x + x1, y + y1);
        plot_pixel(mlx, mlx_win, img, y + x1, x + y1);
        plot_pixel(mlx, mlx_win, img, -x + x1, y + y1);
        plot_pixel(mlx, mlx_win, img, -y + x1, x + y1);
        plot_pixel(mlx, mlx_win, img, -x + x1, -y + y1);
        plot_pixel(mlx, mlx_win, img, -y + x1, -x + y1);
        plot_pixel(mlx, mlx_win, img, x + x1, -y + y1);
        plot_pixel(mlx, mlx_win, img, y + x1, -x + y1);

        y++;
        if (t1 <= 0)
            t1 += 2 * y + 1;
        else
        {
            x--;
            t1 += 2 * (y - x) + 1;
        }
    }
}


//using the midpoint circle algorithm, Jesko's method
// filled circle using midpoint circle algorithm
//https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void midpoint_circle_algorithm(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img)
{
    //(void)x1;
    //(void)y1;
    int t1 = 1 - radius;
    int x = radius;
    int y = 0;
    while (x >= y)
    {
        // Plot points with center at (x1, y1)
        Bresenham_line_algorithm(x_center + x, y_center + y, x_center - x, y_center + y, mlx, mlx_win, img);
        Bresenham_line_algorithm(x_center + y, y_center - x, x_center - y, y_center - x, mlx, mlx_win, img);
        Bresenham_line_algorithm(x_center + x, y_center - y, x_center - x, y_center - y, mlx, mlx_win, img);
        Bresenham_line_algorithm(x_center + y, y_center + x, x_center - y, y_center + x, mlx, mlx_win, img);
        y++;
        if (t1 <= 0)
        {
            t1 += 2 * y + 1;
        }
        else
        {
            x--;
            t1 += 2 * (y - x) + 1;
        }

    }
}