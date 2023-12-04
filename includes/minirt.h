#ifndef MINIRT_H
#define MINIRT_H

#include "../mlx/mlx.h"
#include "../includes/minirt.h"
#include "parse.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_data
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


/* in main.c */
void plot_pixel(void *mlx, void *mlx_win, t_data img, int x, int y,  int color);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	close_window(int keycode, t_vars *vars);
int init_mlx_keyboard_hook(int keycode, t_vars *vars);
int init_mlx_mouse_hook(int keycode, t_vars * vars);
int main(void);

/* in events.c */
int	close_window(int keycode, t_vars *vars);
int mlx_hook_camera_movements(int keycode, t_vars *vars);
int mlx_hook_camera_rotation(int keycode, t_vars *vars);
int mlx_hook_zoom(int keycode, t_vars *vars);

/* in draw_line.c */
void plotLineLow(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);
void plotLineLow(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);
void Bresenham_line_algorithm(int x0, int y0, int x1, int y1, void *mlx, void *mlx_win, t_data img);

/* in utils.c */
int integer_abs(int a);

/* in draw_circle.c */
void midpoint_circle_algorithm_empty(int x1, int y1, int radius, void *mlx, void *mlx_win, t_data img);
void midpoint_circle_algorithm1(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img);
void midpoint_circle_algorithm(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img);
void draw_shaded_circle(int x_center, int y_center, int radius, void *mlx, void *mlx_win, t_data img);


/* in formulas.c */
float * vector_addition(float *vectora, float *vectorb);
float * vector_subtraction(float *vectora, float *vectorb);
float dot_product(float *vectora, float *vectorb);
float *vector_float_multiplication(float *vectora, float value);
float vector_length(float *vectora);
float *cross_product(float *vectora, float *vectorb);
float *find_ray_equation(float *vectora, float *direction_vector, float parameter_value);
float *orthogonal_projection_single_vec(float *vectoru, float *vectorv, float *singular_subspace);
float *convert_orthogonal_project_to_2d(float *vectoru, float *viewpoint_xyz);
float *find_unit_vector(float *vector, float length);

/* in light_types.c */
float *find_reflection_vector(float *incident, float *normal);
float *find_refraction_vector(float *incident, float *normal);
#endif