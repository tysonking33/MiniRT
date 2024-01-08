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
    struct s_vec3 *outward_normal = vec3_div(vec3_sub(record->point_p, sphere->center), sphere->radius);
    set_face_normal(record, r, outward_normal);
    record->normal =  vec3_div(vec3_sub(record->point_p, sphere->center), sphere->radius);

    return 1.0;

}


void set_face_normal(struct s_hit_record *hit_record, struct s_ray *r, struct s_vec3 *outward_normal)
{
    hit_record->front_face_bool = vec3_dot(r->direction, outward_normal);

    if (hit_record->front_face_bool > 0.0)
    {
        hit_record->normal = outward_normal;
    }
    else
    {
        hit_record->normal = vec3_neg(outward_normal);
    }
    
}

void draw_sphere()
{
    int image_width = WIDTH;
    int image_height = HEIGHT;

    FILE *image = fopen("output.ppm", "w");
    fprintf(image, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; ++j) {
        printf("\rScanlines remaining: %d ", (image_height - j));
        for (int i = 0; i < image_width; ++i) {
            float u = (2.0 * i) / (image_width - 1) - 1.0;
            float v = 1.0 - (2.0 * j) / (image_height - 1);

            struct s_ray *ray = make_s_ray(make_vec3(0, 0, 0), make_vec3(u, v, -1.0));
            struct s_vec3 *pixel_color = ray_color(ray);

            write_color(image, pixel_color);

            free_s_ray(ray);
            free_vec3(pixel_color);
        }
    }

    printf("\rDone.                 \n");
    fclose(image);

}