#ifndef MINIRT_H
#define MINIRT_H

#include "../includes/minirt.h"
#include "../includes/parse.h"
#include "../includes/current_values.h"

#include "../mlx/mlx.h"
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
    float height;
    float width; 
} t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;


/* in main.c */
void plot_pixel(void *mlx, void *mlx_win, struct s_data *img, int x, int y,  int color);
void my_mlx_pixel_put(struct s_data *data, int x, int y, int color);
int init_mlx_keyboard_hook(int keycode, struct s_vars *vars);
int init_mlx_keyboard_hook(int keycode, struct s_vars *vars);
int init_mlx_mouse_hook(int keycode, struct s_vars * vars);
void initializeScene(struct s_scene *scene);
int main(void);

/* in events.c */
int	close_window(int keycode, t_vars *vars);
int mlx_hook_camera_movements(int keycode, t_vars *vars);
int mlx_hook_camera_rotation(int keycode, t_vars *vars);
int mlx_hook_zoom(int keycode, t_vars *vars);

/* in vector_calculations.c */
struct s_vector3 *vector_add(struct s_vector3 *A, struct s_vector3 *B);
struct s_vector3 *vector_subtract(struct s_vector3 *A, struct s_vector3 *B);
struct s_vector3 *scalar_multiply(struct s_vector3 *A, float k);
float dot_product(struct s_vector3 *A, struct s_vector3 *B);
struct s_vector3 *cross_product(struct s_vector3 *A, struct s_vector3 *B);
struct s_vector3 *normalize(struct s_vector3 *A);
struct s_vector3 *vector_projection(struct s_vector3 *A, struct s_vector3 *B);
float angle_between_vectors(struct s_vector3 *A, struct s_vector3 *B);
float vector_magnitude(struct s_vector3 *A);
float distance_between_points(struct s_vector3 *P, struct s_vector3 *Q);
struct s_vector2 *rotate_2D_vector(struct s_vector2 *V, float theta);

#endif