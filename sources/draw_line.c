#include "../includes/minirt.h"

void plotLineLow(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;

    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int d = (2 * dy) - dx;
    int y = y0;

    for (int x = x0; x < x1; x++)
    {
        plot_pixel(mlx, mlx_win, img, x, y);
        if (d > 0)
        {
            y = y + yi;
            d = d + (2 * (dy - dx));
        }
        else
        {
            d = d + (2 * dy);
        }
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int d = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y < y1; y++)
    {
        plot_pixel(mlx, mlx_win, img, x, y);
        if (d > 0)
        {
            x = x + xi;
            d = d + (2 * (dx - dy));
        }
        else
        {
            d = d + (2 * dx);
        }
    }
}

//Bresenham's line algorithm, enter the coordinates of the start and end points
//https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
void Bresenham_line_algorithm(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img)
{
    if (integer_abs(y1 - y0) < integer_abs(x1 - x0))
    {
        if (x0 > x1)
        {
            plotLineLow(x1, y1, x0, y0, mlx, mlx_win, img);
        }
        else
        {
            plotLineLow(x0, y0, x1, y1, mlx, mlx_win, img);
        }
    }
    else
    {
        if (y0 > y1)
        {
            plotLineHigh(x1, y1, x0, y0, mlx, mlx_win, img);
        }
        else
        {
            plotLineHigh(x0, y0, x1, y1, mlx, mlx_win, img);
        }
    }
}