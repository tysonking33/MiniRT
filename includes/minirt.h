#ifndef MINIRT_H
#define MINIRT_H

#include "../includes/minirt.h"
#include "../includes/parse.h"
#include "../includes/vec3.h"
#include "../includes/vec3_deviants.h"

#include "../mlx/mlx.h"
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
int main(void);

/* in events.c */
int	close_window(int keycode, t_vars *vars);
int mlx_hook_camera_movements(int keycode, t_vars *vars);
int mlx_hook_camera_rotation(int keycode, t_vars *vars);
int mlx_hook_zoom(int keycode, t_vars *vars);


/* in utils.c */
int integer_abs(int a);

/* in sphere.c */
int hit_sphere(struct s_point3 *center, float radius, struct s_ray *r);
struct s_color *get_ray_color(struct s_ray *r);
void plot_sphere(void *mlx, void *mlx_win, struct s_data *img, struct s_point3 *center, float radius, struct s_ray *camera);
#endif