#include "../includes/cub3d.h"

void plotLineLow(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int yi = 1;
    if (dy < 0)
    {
        yi = -1;
        dy = -dy;
    }
    int D = (2 * dy) - dx;
    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        my_mlx_pixel_put(data, x, y, color);
        if (D > 0)
        {
            y += yi;
            D += 2 * (dy - dx);
        }
        else
        {
            D += 2 * dy;
        }
    }
}

void plotLineHigh(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    int xi = 1;
    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }
    int D = (2 * dx) - dy;
    int x = x0;

    for (int y = y0; y <= y1; y++)
    {
        my_mlx_pixel_put(data, x, y, color);
        if (D > 0)
        {
            x += xi;
            D += (2 * (dx - dy));
        }
        else
        {
            D += 2 * dx;
        }
    }
}

void drawLine(int x0, int y0, int x1, int y1, t_data *data, int color)
{
    if (abs(y1 - y0) < abs(x1 - x0))
    {
        if (x0 > x1)
            plotLineLow(x1, y1, x0, y0, data, color);
        else
            plotLineLow(x0, y0, x1, y1, data, color);
    }
    else
    {
        if (y0 > y1)
            plotLineHigh(x1, y1, x0, y0, data, color);
        else
            plotLineHigh(x0, y0, x1, y1, data, color);
    }
}