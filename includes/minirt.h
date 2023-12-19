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
    struct s_vars *mlx_and_win;
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
struct s_ray * initializeCameraRay(struct s_camera *camera);
void cleanup_scene(struct s_scene *scene);
void cleanup_data(struct s_data *data);
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
struct s_vector3 *ray_at(struct s_ray *ray, float t);


/* in sphere.c */
float hit_sphere(struct s_vector3 *center, float radius, struct s_ray *r);
struct s_vector3 *get_ray_color(struct s_ray *r);
int  write_color(struct s_vector3 *color_vec);
struct s_vector3 *ray_color(struct s_ray *r);
void draw_scene(struct s_scene *scene, struct s_data *img, void *mlx, void *win);
int begin_drawing(struct s_scene *myScene, struct s_data *data);

/* in blue_to_white.c */
struct s_vector3 *ray_color_btw(struct s_ray *r);
void draw_blue_to_white(struct s_scene *scene, struct s_data *img, void *mlx, void *win);

/* in sphere2.c */
int hit_sphere2(struct s_vector3 *center, float radius, struct s_ray *r);
struct s_vector3 * ray_color_sphere(struct s_ray * r);
void draw_sphere(struct s_scene *scene, struct s_data *img, void *mlx, void *win);

/* in debug_and_print.c */
void print_vector3(const char *label, struct s_vector3 *v);
void print_color(const char *label, struct s_color *c);
void print_camera(struct s_camera *camera);
void print_light(struct s_light *light);
void print_sphere(struct s_sphere *sphere);
void print_plane(struct s_plane *plane);
void print_cylinder(struct s_cylinder *cylinder);
void print_ambient_light(struct s_ambient_light *ambientLight);
void print_scene(struct s_scene *scene);
void test_init_vector();

#endif