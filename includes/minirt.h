#ifndef MINIRT_H
#define MINIRT_H

#include "../mlx/mlx.h"
#include "../includes/minirt.h"

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

/* in main.c */
void plot_pixel(void *mlx, void *mlx_win, t_data img, int x, int y);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int main(void);

/* in draw_line.c */
void plotLineLow(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);
void plotLineLow(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);
void Bresenham_line_algorithm(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);

/* in utils.c */
int integer_abs(int a);

/* in draw_circle.c */
void midpoint_circle_algorithm_empty(int x1, int y1, int radius, void *mlx, void *mlx_win, t_data img);
void midpoint_circle_algorithm(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img);

#endif