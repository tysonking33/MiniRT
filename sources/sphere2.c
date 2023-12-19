#include "../includes/minirt.h"

int hit_sphere2(struct s_vector3 *center, float radius, struct s_ray *r)
{
    struct s_vector3 *oc = vector_subtract(r->origin, center);
    /*printf("r->origin->x: %f, r->origin->y: %f, r->origin->z: %f\n", r->origin->x, r->origin->y, r->origin->z);
    printf("center->x: %f, center->y: %f, center->z: %f\n", center->x, center->y, center->z);
    printf("oc->x: %f, oc->y: %f, oc->z: %f\n", oc->x, oc->y, oc->z);
    */
    float a = dot_product(r->direction, r->direction);
    printf("r->direction->x: %f, r->direction->y: %f, r->direction->z: %f\n", r->direction->x, r->direction->y, r->direction->z);
    printf("oc->x: %f, oc->y: %f, oc->z: %f\n", oc->x, oc->y, oc->z);

    float b = 2.0 * dot_product(oc, r->direction);
    float c = dot_product(oc, oc) - radius * radius;
    float discriminant = b * b - 4.0 * a * c;

    printf("a: %f, b: %f, c: %f\n", a,b,c);
    if (discriminant >= 0.0){
        printf("discriminant: %f\n",discriminant);
        return 1;
    }

    return -1;

}

struct s_vector3 *ray_color_sphere(struct s_ray *r)
{
    if (hit_sphere2(&(struct s_vector3){0, 0, -1}, 0.5, r))
    {
        return &(struct s_vector3){1, 0, 0};
    }

    struct s_vector3 *unit_direction = normalize(r->direction);
    float a = 0.5 * (unit_direction->y + 1.0);
    return vector_add(scalar_multiply(&(struct s_vector3){1.0, 1.0, 1.0}, 1.0 - a), scalar_multiply(&(struct s_vector3){0.5, 0.7, 1.0}, a));
}

void draw_sphere(struct s_scene *scene, struct s_data *img, void *mlx, void *win)
{
    for (int i = 0; i < img->width; i++)
    {
        for (int j = 0; j < img->height; j++)
        {
            // Compute the ray direction for each pixel
            float u = (float)i / img->width;
            float v = (float)j / img->height;
            struct s_ray *ray = initializeCameraRay(scene->camera);
            ray->direction = vector_add(ray->direction, scalar_multiply(vector_subtract(&(struct s_vector3){u, v, 0.0}, ray->origin), 10.0));

            // Check if the ray intersects with the sphere
            if (hit_sphere2(scene->sphere->center, scene->sphere->diameter / 2.0, ray) > 0)
            {
                // Get the color for the current pixel using the sphere color function
                struct s_vector3 *color = ray_color_sphere(ray);

                // Convert the color to an integer representation
                int int_color = write_color(color);

                // Plot the pixel on the screen
                plot_pixel(mlx, win, img, i, j, int_color);

                // Clean up the allocated memory for the color
                free(color);
            }

            // Clean up the allocated memory for the ray
            free(ray->direction);
            free(ray->origin);
            free(ray);
        }
    }
}

