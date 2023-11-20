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
        plot_pixel(mlx, mlx_win, img, x + x1, y + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, y + x1, x + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, -x + x1, y + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, -y + x1, x + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, -x + x1, -y + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, -y + x1, -x + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, x + x1, -y + y1, 0x00FF0000);
        plot_pixel(mlx, mlx_win, img, y + x1, -x + y1, 0x00FF0000);

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
void midpoint_circle_algorithm1(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img)
{
    //(void)x1;
    //(void)y1;
    int t1 = 1 - radius;
    int x = radius;
    int y = 0;
    while (x >= y)
    {
        printf("wefsfsdfsdfsd\n");
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


void midpoint_circle_algorithm(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img)
{
    int x = radius;
    int y = 0;
    int radiusError = 1 - x;

    while (x >= y)
    {
        printf("x: %d, y: %d\n", x, y);
        for (int i = x_center - x; i <= x_center + x; i++)
        {
            int image_height = 1080;
            // Limit j to be within the image height bounds
            int j_upper = y_center + y < image_height ? y_center + y : image_height - 1;
            int j_lower = y_center - y >= 0 ? y_center - y : 0;

            for (int j = j_lower; j <= j_upper; j++)
            {
                plot_pixel(mlx, mlx_win, img, i, j, 0x00FF0000);
            }
        }

        for (int i = x_center - y; i <= x_center + y; i++)
        {
            int image_height = 1080;

            // Limit j to be within the image height bounds
            int j_upper = y_center + x < image_height ? y_center + x : image_height - 1;
            int j_lower = y_center - x >= 0 ? y_center - x : 0;

            for (int j = j_lower; j <= j_upper; j++)
            {
                plot_pixel(mlx, mlx_win, img, i, j, 0x00FF0000);
            }
        }

        y++;

        if (radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x + 1);
        }
    }
}


void draw_shaded_circle(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img)
{
    int radius_squared = radius * radius;

    for (int y = -radius; y <= radius; y++) {
        int y_squared = y * y;

        for (int x = -radius; x <= radius; x++) {
            int x_squared = x * x;
            printf("y: %d,x: %d, radius: %d\n", y, x, radius);
            if (x_squared + y_squared <= radius_squared) {
                // Compute intensity based on distance
                int intensity = (1.0 - sqrtf(x_squared + y_squared) / radius) * 255;
                int color = (intensity << 16) | (intensity << 8) | intensity;

                // Update the image directly (assuming plot_pixel modifies img)
                plot_pixel(mlx, mlx_win, img, x_center + x, y_center + y, color);
            }
        }
    }
}
