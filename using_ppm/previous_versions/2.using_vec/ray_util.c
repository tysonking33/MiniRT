#include "vec.h"

struct s_ray *make_s_ray(struct s_vec3 *origin, struct s_vec3 *direction)
{
    struct s_ray *r = (struct s_ray *)malloc(sizeof(struct s_ray));
    r->origin = origin;
    r->direction = direction;
    return r;
}

struct s_vec3 *get_origin(struct s_ray *ray)
{
    return ray->origin;
}
struct s_vec3 *get_direction(struct s_ray *ray)
{
    return ray->direction;
}
struct s_vec3 *at(struct s_ray *ray, float t)
{
    return vec3_add(ray->origin, vec3_mul_float(ray->direction, t));
}

void free_s_ray(struct s_ray *r) {
    //free_vec3(r->origin);
    //free_vec3(r->direction);
    free(r);
}