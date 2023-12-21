#include "vec.h"

struct s_sphere *make_s_sphere(struct s_vec3 *center, float radius)
{
    struct s_sphere * s = (struct s_sphere *)malloc(sizeof(struct s_sphere));
    s->center = center;
    s->radius = radius;
    return s;
}


struct s_vec3 *get_sphere_center(struct s_sphere *src_sphere)
{
    return src_sphere->center;
}
float get_sphere_radius(struct s_sphere *src_sphere)
{
    return src_sphere->radius;
}

float sphere_hit(struct s_sphere *sphere, struct s_ray * r, float ray_tmin, float ray_tmax, struct s_hit_record * record)
{
    struct s_vec3 *oc = vec3_sub(r->origin, sphere->center);
    float a =  vec3_length_squared(r->direction);
    float half_b = vec3_dot(oc, r->direction);
    float c = vec3_length_squared(oc) - powf(sphere->radius, 2);

    float discriminant = powf(half_b, 2) - 4 * a * c;
    if (discriminant < 0)
        return -1.0;

    float sqrtd = sqrtf(discriminant);

    // Find the nearest root that lies in the acceptable range.
    float root = (-half_b - sqrtd) / a;
    if (root <= ray_tmin || ray_tmax <= root)
    {
        root = (-half_b + sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
            return -1.0;
    }

    record->t = root;
    record->point_p = at(r, record->t);
    record->normal =  vec3_div(vec3_sub(record->point_p, sphere->center), sphere->radius);

    return 1.0;

}