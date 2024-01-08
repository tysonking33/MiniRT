#include "raytracing.h"

struct s_vector *make_vector(float r, float g, float b)
{
    struct s_vector *new_vector = &(struct s_vector){r,g,b};

    return new_vector;
}

struct s_point *make_point(float r, float g, float b)
{
    struct s_point *new_point = &(struct s_point){r,g,b};

    return new_point;
}

struct s_color *make_color(float r, float g, float b)
{
    struct s_color *new_color = &(struct s_color){r,g,b};

    return new_color;
}

struct s_ray *make_s_ray(struct s_vector *origin, struct s_vector *direction)
{
    struct s_ray *r = (struct s_ray *)malloc(sizeof(struct s_ray));
    r->origin = origin;
    r->direction = direction;
    return r;
}

struct s_vector *get_origin(struct s_ray *ray)
{
    return ray->origin;
}
struct s_vector *get_direction(struct s_ray *ray)
{
    return ray->direction;
}
struct s_vector *at(struct s_ray *ray, float t)
{
    return add_vectors(ray->origin, multiply_vector_scalar(ray->direction, t));
}

void free_s_ray(struct s_ray *r) {
    //free_vec3(r->origin);
    //free_vec3(r->direction);
    free(r);
}