#ifndef RAYTRACING_H
#define RAYTRACING_H

# define WIDTH 800
# define HEIGHT 800

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
//#include "mlx.h"

typedef struct s_vector
{
    float x;
    float y;
    float z;
} t_vector;

typedef struct s_point
{
    float x;
    float y;
    float z;
} t_point;

typedef struct s_color
{
    float red;
    float green;
    float blue;
} t_color;

typedef struct s_ray{
    struct s_vector *origin;
    struct s_vector *direction;
}   t_ray;


typedef struct s_material
{
    struct s_color *color;
    float reflection_coefficient;
} t_material;

typedef struct s_light
{
    struct s_point *position;
    float *brightness;
} t_light;

typedef struct s_camera
{
    struct s_point *position;
    struct s_vector *orientation;
    float fov;
} t_camera;

typedef struct s_sphere
{
    struct s_point *center;
    float diameter;
    struct s_material *material;
} t_sphere;

typedef struct s_plane
{
    struct s_point *point;
    struct s_vector *normal;
    struct s_material *material;
} t_plane;

typedef struct s_cylinder
{
    struct s_point *center;
    struct s_vector *axis;
    float diameter;
    float height;
    struct s_material *material;
} t_cylinder;

typedef struct s_scene
{
    float ambient_ratio;
    struct s_color *ambient_color;
    struct s_camera *camera;
    struct s_light *light;
    struct s_sphere *sphere;
    struct s_plane *plane;
    struct s_cylinder *cylinder;
} t_scene;

typedef struct s_intersection
{
    float hit;
    float t;
    struct s_vector *normal;
    struct s_material *material;
} t_intersection;

/* start main.c */
int main();
void draw_gradient();
void write_color(FILE *file, struct s_vector *color);
/* end main.c */

/* start initalisation.c */
struct s_vector *make_vector(float r, float g, float b);
struct s_point *make_point(float r, float g, float b);
struct s_color *make_color(float r, float g, float b);
struct s_ray *make_s_ray(struct s_vector *origin, struct s_vector *direction);
struct s_vector *get_origin(struct s_ray *ray);
struct s_vector *get_direction(struct s_ray *ray);
struct s_vector *at(struct s_ray *ray, float t);
void free_s_ray(struct s_ray *r);
/* end initalisation.c */

/* start vector_utils.c */
float get_vector_x(struct s_vector *v);
float get_vector_y(struct s_vector *v);
float get_vector_z(struct s_vector *v);
/* end vector_utils.c */

/* start vector_calculation.c */
struct s_vector *add_vectors(struct s_vector *v1, struct s_vector *v2);
struct s_vector *subtract_vectors(struct s_vector *v1, struct s_vector *v2);
struct s_vector *multiply_vector_scalar(struct s_vector *v, float scalar);
float dot_product(struct s_vector *v1, struct s_vector *v2);
struct s_vector *cross_product(struct s_vector *v1, struct s_vector *v2);
struct s_vector *normalize_vector(struct s_vector *v);
struct s_vector *reflect_vector(struct s_vector *incident, struct s_vector *normal);
struct s_vector *add_scalar(struct s_vector *v, float t);
struct s_vector *subtract_scalar(struct s_vector *v, float t);
struct s_vector *divide_scalar(struct s_vector *v, float t);
void free_vector(struct s_vector *v);
/* end vector_calculation.c */

/* start draw_circle.c */
float hit_sphere(struct s_vector *center, float radius, struct s_ray *r);
struct s_vector *ray_color(struct s_ray *r);
void draw_circle();

/* end draw_circle.c */

#endif